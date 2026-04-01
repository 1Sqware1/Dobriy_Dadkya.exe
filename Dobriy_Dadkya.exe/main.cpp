#include <windows.h>
#include <mmsystem.h>
#include "resource.h" 

#pragma comment(lib, "winmm.lib")
#pragma warning(disable: 28251)

// Объявляем функцию для окна с таймером
extern "C" int WINAPI MessageBoxTimeoutA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    // 1. ТВОЁ ПЕРВОЕ ПРЕДУПРЕЖДЕНИЕ (ПОЛНЫЙ ТЕКСТ)
    int firstQuiz = MessageBoxA(
        NULL,
        "ВНИМАНИЕ!\n\nВы запускаете  'Добрый дядька.exe'.\nЭто может привести к потере данных на вашем ПК.\n Рекомендуется запускать данную программу ТОЛЬКО НА ВИРТУАЛЬНОЙ МАШИНЕ!!!!\n Вы хотите продолжить??",
        "УРОДЫ КОНЧЕНЫЕ",
        MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2
    );

    if (firstQuiz == IDNO) return 0;

    // 2. ТВОЁ ВТОРОЕ ПРЕДУПРЕЖДЕНИЕ (ПОЛНЫЙ ТЕКСТ)
    int secondQuiz = MessageBoxA(
        NULL,
        "ЭТО ПОСЛЕДНИЕ ПРЕДУПРЕЖДЕНИЕ!\n\nАвтор не несёт отвесности за вашем Компьютером.\n\nBy Sqware_",
        "КРИТИЧЕСКАЯ ОШИБКА / FINAL WARNING",
        MB_YESNO | MB_ICONSTOP | MB_DEFBUTTON2
    );

    if (secondQuiz == IDNO) return 0;

    // 3. ОКНО-ТАЙМЕР (ИСЧЕЗНЕТ ЧЕРЕЗ 3 СЕКУНДЫ)
    MessageBoxTimeoutA(NULL, "Добрый дядька заходит в систему...", "STATUS", MB_OK | MB_ICONINFORMATION, 0, 3000);

    // 4. ТРЕК НАЧИНАЕТ ИГРАТЬ СРАЗУ ПОСЛЕ ЗАКРЫТИЯ ОКНА
    // Используем IDR_WAVE1 из твоего resource.h
    PlaySoundA(MAKEINTRESOURCEA(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);

    // Зацикливаем программу, чтобы музыка не выключилась
    // Здесь же в будущем будет цикл для визуальных эффектов
    while (true) {
        Sleep(100);
    }

    return 0;
}