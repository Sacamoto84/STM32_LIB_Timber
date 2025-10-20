Timber timber = Timber();

timber.init(&huart1);

timber.clear();
timber.print("Error Привет");
timber.e("Error Привет");
timber.i("Info Привет");
timber.w("Warning Привет");