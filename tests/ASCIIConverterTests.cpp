#include <src/Renderer.h>
#include <src/ASCIIConverter.h>
#include <src/Pixel.h>
#include <src/Input.h>
#include <src/Config.h>

#include <gtest/gtest.h>


// ============================================================
// GOOGLE TEST — ШПАРГАЛКА ДЛЯ Image2ASCII
// ============================================================
//
// 1. ПОДКЛЮЧЕНИЕ
//
// #include <gtest/gtest.h>
//
// ============================================================
// 2. СТРУКТУРА ТЕСТА
// ============================================================
//
// TEST(TestSuiteName, TestName)
// {
//     // Arrange — подготовить данные
//     int a = 2;
//     int b = 2;
//
//     // Act — выполнить проверяемое действие
//     int result = a + b;
//
//     // Assert — проверить результат
//     EXPECT_EQ(result, 4);
// }
//
// TestSuiteName — имя группы тестов.
// TestName      — имя конкретного теста.
//
// ============================================================
// 3. ОСНОВНЫЕ ПРОВЕРКИ
// ============================================================
//
// EXPECT_EQ(a, b);     // a == b
// EXPECT_NE(a, b);     // a != b
// EXPECT_TRUE(expr);   // выражение истинно
// EXPECT_FALSE(expr);  // выражение ложно
// EXPECT_LT(a, b);     // a < b
// EXPECT_LE(a, b);     // a <= b
// EXPECT_GT(a, b);     // a > b
// EXPECT_GE(a, b);     // a >= b
//
// EXPECT_STREQ(a, b);  // C-строки равны по содержимому
//
// EXPECT_NEAR(a, b, epsilon);
// // Числа отличаются не более чем на epsilon.
//
// ============================================================
// 4. EXPECT И ASSERT
// ============================================================
//
// EXPECT_EQ(a, b);
// // При ошибке тест продолжается.
//
// ASSERT_EQ(a, b);
// // При ошибке текущий тест немедленно прекращается.
//
// Используй ASSERT, когда дальнейшие проверки бессмысленны
// без успешного выполнения текущей.
//
// ============================================================
// 5. ИМЕНА ТЕСТОВ
// ============================================================
//
// TEST(BrightnessTests, ReturnsDarkestSymbol)
// {
//     // Проверка символа при минимальной яркости.
// }
//
// TEST(BrightnessTests, ReturnsLightestSymbol)
// {
//     // Проверка символа при максимальной яркости.
// }
//
// TEST(BrightnessTests, HandlesMediumBrightness)
// {
//     // Проверка промежуточной яркости.
// }
//
// TEST(ConfigTests, UsesSmallSymbolSet)
// {
//     // Проверка набора Small.
// }
//
// TEST(ConfigTests, UsesMediumSymbolSet)
// {
//     // Проверка набора Medium.
// }
//
// TEST(ConfigTests, UsesLargeSymbolSet)
// {
//     // Проверка набора Large.
// }
//
// ============================================================
// 6. TEST_F — ОБЩАЯ ПОДГОТОВКА ДЛЯ НЕСКОЛЬКИХ ТЕСТОВ
// ============================================================
//
// class BrightnessTests : public ::testing::Test
// {
// protected:
//     void SetUp() override
//     {
//         // Подготовка объектов перед каждым тестом.
//     }
//
//     void TearDown() override
//     {
//         // Очистка после каждого теста, если необходима.
//     }
// };
//
// TEST_F(BrightnessTests, ReturnsDarkestSymbol)
// {
//     // Здесь доступна подготовка из SetUp().
// }
//
// TEST_F(BrightnessTests, ReturnsLightestSymbol)
// {
//     // SetUp() снова выполняется перед этим тестом.
// }
//
// ============================================================
// 7. TEST_P — ПАРАМЕТРИЗОВАННЫЕ ТЕСТЫ
// ============================================================
//
// Используй, если одну и ту же логику нужно проверить
// на нескольких наборах входных данных.
//
// TEST_P(BrightnessParameterizedTests, ReturnsExpectedSymbol)
// {
//     // GetParam() возвращает текущий тестовый параметр.
// }
//
// // Для запуска TEST_P нужны:
// // - класс-наследник ::testing::TestWithParam<T>;
// // - INSTANTIATE_TEST_SUITE_P(...);
// // - набор параметров через Values(...) или другой генератор.
//
// ============================================================
// 8. ПРОВЕРКА ИСКЛЮЧЕНИЙ
// ============================================================
//
// EXPECT_THROW(Function(), std::runtime_error);
// // Проверяет, что выброшено исключение указанного типа.
//
// EXPECT_NO_THROW(Function());
// // Проверяет отсутствие исключения.
//
// EXPECT_ANY_THROW(Function());
// // Проверяет, что выброшено какое-либо исключение.
//
// ============================================================
// 9. ЗАПУСК ТЕСТОВ В POWERSHELL
// ============================================================
//
// Все тесты:
// .\out\build\x64-Debug\Image2ASCII_tests.exe
//
// Показать список тестов:
// .\out\build\x64-Debug\Image2ASCII_tests.exe --gtest_list_tests
//
// Запустить один тест:
// .\out\build\x64-Debug\Image2ASCII_tests.exe
//     --gtest_filter="BrightnessTests.ReturnsDarkestSymbol"
//
// Запустить группу:
// .\out\build\x64-Debug\Image2ASCII_tests.exe
//     --gtest_filter="BrightnessTests.*"
//
// Исключить конкретный тест:
// .\out\build\x64-Debug\Image2ASCII_tests.exe
//     --gtest_filter="-BrightnessTests.ReturnsDarkestSymbol"
//
// ============================================================
// 10. ЗАПУСК ЧЕРЕЗ CTEST
// ============================================================
//
// Собрать тесты:
// cmake --build out/build/x64-Debug --target Image2ASCII_tests
//
// Запустить все обнаруженные CTest тесты:
// ctest --test-dir out/build/x64-Debug -C Debug --output-on-failure
//
// Вывести подробности:
// ctest --test-dir out/build/x64-Debug -C Debug -V
//
// ============================================================
// 11. ЧТО ТЕСТИРОВАТЬ В Image2ASCII
// ============================================================
//
// ASCIIConverter:
// - минимальная яркость (0);
// - максимальная яркость (255);
// - промежуточная яркость;
// - наборы Small, Medium и Large;
// - правильное соответствие яркости символу.
//
// Config:
// - значения по умолчанию;
// - корректные параметры конфигурации;
// - граничные значения ширины и высоты.
//
// Input:
// - корректный ввод команды;
// - отсутствие необработанных данных;
// - обработка некорректного ввода, если предусмотрена.
//
// Renderer:
// - форматирование результата;
// - корректное преобразование пикселей в символы;
// - обработка пустых или некорректных данных, если допустима.
//
// ============================================================
// 12. ВАЖНЫЕ ПРАВИЛА
// ============================================================
//
// - Каждый тест проверяет конкретное поведение.
// - Не проверяй только то, что функция вообще вызывается.
// - Проверяй ожидаемый результат.
// - Проверяй границы: минимум, максимум, крайние случаи.
// - Тесты должны быть независимыми друг от друга.
// - Не полагайся на порядок запуска тестов.
// - Не используй реальные изображения там, где достаточно
//   маленького искусственного тестового примера.
// - Не делай тест зависимым от текущей рабочей директории,
//   внешней сети или локальных файлов без необходимости.
// - EXPECT проверяет условие, но сам по себе не исправляет код.
// - Тест, который всегда проходит, не доказывает корректность.
//
// ============================================================
// 13. СБОРКА C++17
// ============================================================
//
// Для отдельного файла без CMake GoogleTest обычно требует
// настройки и линковки библиотеки.
//
// В твоём проекте GoogleTest уже подключён через CMake,
// поэтому используй CMake и не линкуй библиотеку вручную.
//
// ============================================================



TEST(ASCIIConverterTest, ReturnsDarkestSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(0);
	converter.setGreen(0);
	converter.setRed(0);

	ASSERT_EQ(converter.getBrightness(), 0);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '@');
	
}

TEST(ASCIIConverterTest, ReturnsBrightestSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(255);
	converter.setGreen(255);
	converter.setRed(255);

	ASSERT_EQ(converter.getBrightness(), 255);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), ' ');	

}

TEST(ASCIIConverterTest, ReturnsAverageBrightnessSymbol) {

	ASCIIConverter converter;
	Config conf;

	converter.setBlue(128);
	converter.setGreen(128);
	converter.setRed(128);

	conf.symbols = Small;	
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '=');

	conf.symbols = Medium;
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '1');

	conf.symbols = Large;
	EXPECT_NEAR(converter.getBrightness(), 128, 0.1);
	EXPECT_EQ(converter.BrightnessToASCIISymbol(conf), '{');
}
