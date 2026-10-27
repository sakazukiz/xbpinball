#include <cstdint>

struct X86Context {
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp, esi, edi;
};

// Penambal Crash Audio bawaan (tetap dipertahankan)
bool FixNullAudio(X86Context& ctx, uint8_t* base) {
    ctx.eax = 0;
    ctx.esi = 0x10000000;
    return true;
}

// Bypass Video XMV yang Aman & Alami
bool BypassXMVPlayer(X86Context& ctx, uint8_t* base) {
    // 1. Beritahu engine game bahwa fungsi pemutar video tereksekusi dengan 'sukses'
    ctx.eax = 1;

    // 2. Fungsi ini menerima output parameter di argumen kedua (esp + 8).
    // Game menunggu nilai pointer ini di-set ke 0 sebagai tanda video selesai.
    uint32_t out_param_ptr = *(uint32_t*)(base + ctx.esp + 8);
    if (out_param_ptr != 0) {
        *(uint32_t*)(base + out_param_ptr) = 0;
    }

    // 3. Langsung jalankan instruksi 'ret' untuk melompati seluruh fungsi
    return true;
}