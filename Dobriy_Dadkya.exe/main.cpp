#include <windows.h>
#include <mmsystem.h>
#include <digitalv.h> 
#include "resource.h" 

#pragma comment(lib, "winmm.lib")
#pragma warning(disable: 28251)
#pragma warning(disable: 4996)

// Функция для проигрывания видео
void PlayVideoSync(LPCSTR fileName) {
    char fullPath[MAX_PATH];
    GetFullPathNameA(fileName, MAX_PATH, fullPath, NULL);

    char command[MAX_PATH + 128];
    wsprintfA(command, "open \"%s\" type mpegvideo alias intro", fullPath);
    mciSendStringA(command, NULL, 0, NULL);

    // Флаг 'wait'
    mciSendStringA("play intro fullscreen wait", NULL, 0, NULL);

    mciSendStringA("close intro", NULL, 0, NULL);
}

extern "C" int WINAPI MessageBoxTimeoutA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    // 1. ПРЕДУПРЕЖДЕНИЯ
    if (MessageBoxA(NULL, "ВНИМАНИЕ!\n\nВы запускаете  'Добрый дядька.exe'.\nЭто может привести к потере данных на вашем ПК.\n Рекомендуется запускать данную программу ТОЛЬКО на виртуальной машине!\n Вы хотите продолжить??", "УРОДЫ КОНЧЕНЫЕ", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO) return 0;
    if (MessageBoxA(NULL, "ЭТО ПОСЛЕДНИЕ ПРЕДУПРЕЖДЕНИЕ!\n\nАвтор не несёт отвесности за вашем Компьютером.\n\nBy Sqware_", "КРИТИЧЕСКАЯ ОШИБКА / FINAL WARNING", MB_YESNO | MB_ICONSTOP | MB_DEFBUTTON2) == IDNO) return 0;

    // 2. ТАЙМЕР ПЕРЕД СТАРТОМ
    MessageBoxTimeoutA(NULL, "Добрый дядька заходит в систему...", "STATUS", MB_OK | MB_ICONINFORMATION, 0, 3000);

    // --- 3. ЗАПУСК ЗВУКА И ВИДЕО
    PlaySoundA(MAKEINTRESOURCEA(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);

    // Сразу же запуск видео
    PlayVideoSync("intro.wmv");

    // --- 4. ЗАПУСК ЭФФЕКТОВ ---
    HDC hdc = GetDC(NULL);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);

    while (true) {
        // Мигание инверсией
        PatBlt(hdc, 0, 0, sw, sh, DSTINVERT);

        // Эффект дрожания
        BitBlt(hdc, rand() % 10 - 5, rand() % 10, sw, sh, hdc, 0, 0, SRCCOPY);

        Sleep(30);
    }

    return 0;
}