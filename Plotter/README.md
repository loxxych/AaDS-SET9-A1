# SET9_A1 Plotter

Python-проект для построения графиков через `matplotlib` по данным из `../TestResults/results.csv`.

Установка зависимости:

```bash
python3 -m pip install -r requirements.txt
```

Запуск из папки `Plotter`:

```bash
python3 plot_results.py
```

По умолчанию скрипт создает PNG-файлы в папке `Plotter/plots`:

- `time_<data_type>.png` — среднее время работы алгоритмов;
- `comparisons_<data_type>.png` — среднее число посимвольных сравнений.

Можно передать свои пути:

```bash
python3 plot_results.py --input ../TestResults/results.csv --output plots
```
