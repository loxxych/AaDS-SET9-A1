from __future__ import annotations

import argparse
import csv
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter


DEFAULT_INPUT = Path(__file__).resolve().parent.parent / "TestResults" / "results.csv"
DEFAULT_OUTPUT = Path(__file__).resolve().parent / "plots"

ALGORITHM_COLORS = {
    "StandardMergeSort": "#2f6f9f",
    "StandardQuickSort": "#c44e52",
    "StringMergeSort": "#55a868",
    "StringQuickSort": "#8172b3",
    "RadixSort": "#4c4c4c",
    "RadixSortWithQuickSwitch": "#dd8452",
}

METRICS = {
    "average_time_microseconds": ("time", "Среднее время, мкс"),
    "average_char_comparisons": ("comparisons", "Среднее число посимвольных сравнений"),
}

DATA_TYPE_LABELS = {
    "random": "случайные данные",
    "reversed": "обратно отсортированные данные",
    "almost_sorted": "почти отсортированные данные",
}


@dataclass(frozen=True)
class ResultRow:
    algorithm: str
    data_type: str
    array_size: int
    max_string_size: int
    average_time_microseconds: float
    average_char_comparisons: float


def read_results(path: Path) -> list[ResultRow]:
    with path.open("r", newline="", encoding="utf-8") as file:
        reader = csv.DictReader(file)
        rows = []

        for row in reader:
            max_string_size_key = "max_string_size" if "max_string_size" in row else "string_size"
            rows.append(
                ResultRow(
                    algorithm=row["algorithm"],
                    data_type=row["data_type"],
                    array_size=int(row["array_size"]),
                    max_string_size=int(row[max_string_size_key]),
                    average_time_microseconds=float(row["average_time_microseconds"]),
                    average_char_comparisons=float(row["average_char_comparisons"]),
                )
            )

    if not rows:
        raise ValueError(f"No data rows found in {path}")

    return rows


def group_rows(rows: list[ResultRow]) -> dict[str, dict[str, list[ResultRow]]]:
    grouped: dict[str, dict[str, list[ResultRow]]] = defaultdict(lambda: defaultdict(list))

    for row in rows:
        grouped[row.data_type][row.algorithm].append(row)

    return {
        data_type: {
            algorithm: sorted(algorithm_rows, key=lambda item: item.array_size)
            for algorithm, algorithm_rows in sorted(algorithm_groups.items())
        }
        for data_type, algorithm_groups in sorted(grouped.items())
    }


def thousands_formatter(value: float, _: int) -> str:
    if abs(value) >= 1000:
        return f"{value / 1000:g}k"

    return f"{value:g}"


def draw_chart(
    data_type: str,
    algorithm_groups: dict[str, list[ResultRow]],
    metric: str,
    output_dir: Path,
) -> Path:
    file_prefix, y_label = METRICS[metric]
    fig, ax = plt.subplots(figsize=(12, 7), dpi=160)

    for algorithm, rows in algorithm_groups.items():
        x_values = [row.array_size for row in rows]
        y_values = [getattr(row, metric) for row in rows]

        ax.plot(
            x_values,
            y_values,
            marker="o",
            markersize=3.2,
            linewidth=1.8,
            color=ALGORITHM_COLORS.get(algorithm),
            label=algorithm,
        )

    data_type_label = DATA_TYPE_LABELS.get(data_type, data_type)

    ax.set_title(f"{y_label}: {data_type_label}", fontsize=15, fontweight="bold", pad=14)
    ax.set_xlabel("Размер массива")
    ax.set_ylabel(y_label)
    ax.grid(True, color="#dddddd", linewidth=0.8)
    ax.set_xlim(left=0)
    ax.yaxis.set_major_formatter(FuncFormatter(thousands_formatter))
    ax.legend(loc="center left", bbox_to_anchor=(1.02, 0.5), frameon=False)

    fig.tight_layout()

    path = output_dir / f"{file_prefix}_{data_type}.png"
    fig.savefig(path, bbox_inches="tight")
    plt.close(fig)

    return path


def write_charts(rows: list[ResultRow], output_dir: Path) -> list[Path]:
    output_dir.mkdir(parents=True, exist_ok=True)
    chart_paths = []

    for data_type, algorithm_groups in group_rows(rows).items():
        for metric in METRICS:
            chart_paths.append(draw_chart(data_type, algorithm_groups, metric, output_dir))

    return chart_paths


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Build matplotlib PNG charts for SET9_A1 sorting measurements.")
    parser.add_argument("--input", type=Path, default=DEFAULT_INPUT, help="Path to results.csv")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT, help="Directory for generated PNG charts")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    rows = read_results(args.input)
    chart_paths = write_charts(rows, args.output)

    for path in chart_paths:
        print(path)


if __name__ == "__main__":
    main()
