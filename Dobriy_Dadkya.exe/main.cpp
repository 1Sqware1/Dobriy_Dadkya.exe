#include <windows.h>
#include <mmsystem.h>
#include <digitalv.h> 
#include "resource.h" 
#include <vector>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma warning(disable: 28251)
#pragma warning(disable: 4996)

// Видео
void PlayVideoSync(LPCSTR fileName) {
    char fullPath[MAX_PATH];
    GetFullPathNameA(fileName, MAX_PATH, fullPath, NULL);
    char command[MAX_PATH + 128];
    wsprintfA(command, "open \"%s\" type mpegvideo alias intro", fullPath);
    mciSendStringA(command, NULL, 0, NULL);
    mciSendStringA("play intro fullscreen wait", NULL, 0, NULL);
    mciSendStringA("close intro", NULL, 0, NULL);
}

// Обои
void ChangeWallpaper(LPCSTR fileName) {
    char fullPath[MAX_PATH];
    if (GetFullPathNameA(fileName, MAX_PATH, fullPath, NULL)) {
        SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)fullPath, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
    }
}

extern "C" int WINAPI MessageBoxTimeoutA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    // Предупреждение 1
    if (MessageBoxA(NULL, "ВНИМАНИЕ!\n\nВы запускаете  'Добрый дядька.exe'.\nЭто может привести к потере данных на вашем ПК.\n Рекомендуется запускать данную программу ТОЛЬКО на виртуальной машине!\n Вы хотите продолжить??", "УРОДЫ КОНЧЕНЫЕ", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO) return 0;

    // Предупреждение 2
    if (MessageBoxA(NULL, "ЭТО ПОСЛЕДНИЕ ПРЕДУПРЕЖДЕНИЕ!\n\nАвтор не несёт отвесности за вашем Компьютером.\n\nBy Sqware_", "КРИТИЧЕСКАЯ ОШИБКА / FINAL WARNING", MB_YESNO | MB_ICONSTOP | MB_DEFBUTTON2) == IDNO) return 0;

    // Таймер
    MessageBoxTimeoutA(NULL, "Добрый дядька заходит в систему...", "STATUS", MB_OK | MB_ICONINFORMATION, 0, 3000);

    // Звук
    PlaySoundA(MAKEINTRESOURCEA(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);

    // Видео
    PlayVideoSync("intro.wmv");

    HDC hdc = GetDC(NULL);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);

    // Обои
    ChangeWallpaper("wallpaper.jpg");

    long long iter = 0;
    const char* phrases[] = {
        "ЗАПРОСИ ЕБАЛО СЛОМАЮ ТЕБЕ СУКА",
        "ПОШЁЛ ТЫ НАХУЙ ПИДОР БЛЯТЬ!",
        "ТЫ ЧЁ ТВОРИШЬ, УРОД?",
        "Что? Ты иглаешь в Роблокс? Не ну это Абаюдна ТЬФУ!!",
        "ЧЁРНОМАЗЫЙ ПИДОРАС!",
        "СЪЕБАЛСЯ ОТСЮДА НАХУЙ КАК И ДРУГИЕ ПИДОРАСЫ!!"
    };

    while (true) {
        iter++;

        // Чернение
        if (iter > 10 && iter % 6 == 0) {
            BitBlt(hdc, rand() % 3, rand() % 3, sw, sh, hdc, rand() % 3, rand() % 3, SRCAND);
        }

        // Фигуры без заливки
        if (iter > 80 && iter % 2 == 0) {
            HPEN hPen = CreatePen(PS_SOLID, rand() % 3 + 1, RGB(rand() % 255, rand() % 255, rand() % 255));
            SelectObject(hdc, hPen);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));

            int x1 = rand() % sw, y1 = rand() % sh;
            int x2 = rand() % sw, y2 = rand() % sh;
            int type = rand() % 4;

            if (type == 0) { MoveToEx(hdc, x1, y1, NULL); LineTo(hdc, x2, y2); }
            else if (type == 1) { Ellipse(hdc, x1, y1, x2, y2); }
            else if (type == 2) { Rectangle(hdc, x1, y1, x2, y2); }
            else { POINT pts[3] = { {x1, y1}, {x2, y2}, {rand() % sw, rand() % sh} }; Polygon(hdc, pts, 3); }

            DeleteObject(hPen);
        }

        // Инверсия
        if (iter > 150 && iter % 20 == 0) {
            PatBlt(hdc, 0, 0, sw, sh, DSTINVERT);
        }

        // Эффект тонель
        if (iter > 300) {
            StretchBlt(hdc, 20, 20, sw - 40, sh - 40, hdc, 0, 0, sw, sh, SRCCOPY);
        }

        // Ошибки поверх всего
        if (iter > 400 && iter % 100 == 0) {
            CreateThread(NULL, 0, [](LPVOID lpParam) -> DWORD {
                const char** p = (const char**)lpParam;
                MessageBoxA(NULL, p[rand() % 6], "УРОДЫ КОНЧЕНЫЕ", MB_OK | MB_ICONERROR | MB_TOPMOST);
                return 0;
                }, (LPVOID)phrases, 0, NULL);
        }

        // Тряска
        BitBlt(hdc, rand() % 12 - 6, rand() % 12 - 6, sw, sh, hdc, 0, 0, SRCCOPY);

        Sleep(20);
    }
    return 0;
}