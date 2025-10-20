Создание переменной
```cpp
Timber timber = Timber();
```

В main инициируем UART
```cpp
timber.init(&huart1);
```

Использование

```cpp
//Команда на терминал очистки экрана
timber.clear();
```

timber.print("Error Привет");

timber.e("Error Привет");

timber.i("Info Привет");

timber.w("Warning Привет");
