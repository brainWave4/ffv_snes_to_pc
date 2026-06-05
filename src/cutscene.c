// Bank Range: C3
#include "includes/cutscene.h"

// for ExecSound_ext
#include "includes/sound.h"

static void initDecomp(void); // Incomplete
static void decomp(void); // Incomplete
static void func_7f8000(void); // Incomplete
static void func_7f803a(void); // Incomplete
static void cutscene_titleCredits(void); // Incomplete
static void func_7f8434(void); // Incomplete
static void func_7f846f(void); // Incomplete
static void func_7f8498(void); // Incomplete
static void func_7f84bb(void); // Incomplete
static void cutscene_fallingMeteor(void); // Incomplete
static void func_7f8660(void); // Incomplete
static void func_7f867d(void); // Incomplete
static void cutscene03(void); // Incomplete
static void cutscene_flashRedShort(void); // Incomplete
static void cutscene_flashRedLong(void); // Incomplete
static void func_7f8a4e(void); // Incomplete
static void cutscene_lightningBolt(void); // Incomplete
static void cutscene_purpleSparklies(void); // Incomplete
static void func_7f8c09(void); // Incomplete
static void cutscene_endingCredits(void); // Incomplete
static void func_7f945d(void); // Incomplete
static void func_7f9465(void); // Incomplete
static void func_7f94a5(void); // Incomplete
static void func_7f95a1(void); // Incomplete
static void func_7f95ab(void); // Incomplete
static void func_7f95d9(void); // Incomplete
static void func_7f95ec(void); // Incomplete
static void func_7f95ff(void); // Incomplete
static void func_7f963a(void); // Incomplete
static void func_7f9679(void); // Incomplete
static void func_7f96b8(void); // Incomplete
static void func_7f96f9(void); // Incomplete
static void func_7f970e(void); // Incomplete
static void func_7f9753(void); // Incomplete
static void func_7f9780(void); // Incomplete
static void func_7f97ad(void); // Incomplete
static void func_7f97f8(void); // Incomplete
static void func_7f983b(void); // Incomplete
static void func_7f988a(void); // Incomplete
static void func_7f98d0(void); // Incomplete
static void func_7f9943(void); // Incomplete
static void func_7f99b6(void); // Incomplete
static void func_7f99ea(void); // Incomplete
static void func_7f9a1e(void); // Incomplete
static void func_7f9a29(void); // Incomplete
static void func_7f9a39(void); // Incomplete
static void func_7f9a49(void); // Incomplete
static void func_7f9a57(void); // Incomplete
static void func_7f9a65(void); // Incomplete
static void func_7f9a73(void); // Incomplete
static void func_7f9a81(void); // Incomplete
static void func_7f9a8f(void); // Incomplete
static void func_7f9a98(void); // Incomplete
static void func_7f9aa1(void); // Incomplete
static void func_7f9aa8(void); // Incomplete
static void func_7f9ab1(void); // Incomplete
static void func_7f9abd(void); // Incomplete
static void func_7f9ac9(void); // Incomplete
static void func_7f9ad9(void); // Incomplete
static void func_7f9ae4(void); // Incomplete
static void func_7f9af2(void); // Incomplete
static void func_7f9deb(void); // Incomplete
static void func_7f9f2c(void); // Incomplete
static void func_7fa244(void); // Incomplete
static void func_7fa3a0(void); // Incomplete
static void func_7fa3b6(void); // Incomplete
static void func_7fa50e(void); // Incomplete
static void func_7fa527(void); // Incomplete
static void func_7fa538(void); // Incomplete
static void func_7fa549(void); // Incomplete
static void func_7fa554(void); // Incomplete
static void func_7fa562(void); // Incomplete
static void func_7fa570(void); // Incomplete
static void func_7fa797(void); // Incomplete
static void func_7fa811(void); // Incomplete
static void func_7fa8c6(void); // Incomplete
static void func_7fa963(void); // Incomplete
static void func_7faafc(void); // Incomplete
static void func_7fab3b(void); // Incomplete
static void func_7fab7a(void); // Incomplete
static void func_7fac2a(void); // Incomplete
static void func_7fac54(void); // Incomplete
static void func_7fac78(void); // Incomplete
static void func_7facab(void); // Incomplete
static void func_7faccc(void); // Incomplete
static void func_7fad0d(void); // Incomplete
static void func_7fad23(void); // Incomplete
static void func_7fae01(void); // Incomplete
static void func_7fae2d(void); // Incomplete
static void func_7fae37(void); // Incomplete
static void func_7fae70(void); // Incomplete
static void func_7faebc(void); // Incomplete
static void func_7faf08(void); // Incomplete
static void func_7faf81(void); // Incomplete
static void func_7fafa1(void); // Incomplete
static void func_7fafae(void); // Incomplete
static void func_7fafc1(void); // Incomplete
static void func_7fafed(void); // Incomplete
static void func_7faff3(void); // Incomplete
static void func_7faff9(void); // Incomplete
static void func_7fafff(void); // Incomplete
static void func_7fb035(void); // Incomplete
static void func_7fb046(void); // Incomplete
static void func_7fb067(void); // Incomplete
static void func_7fb08a(void); // Incomplete
static void func_7fb0ad(void); // Incomplete
static void func_7fb124(void); // Incomplete
static void func_7fb19f(void); // Incomplete
static void func_7fb1fd(void); // Incomplete
static void func_7fb21d(void); // Incomplete
static void func_7fb273(void); // Incomplete
static void func_7fb29e(void); // Incomplete
static void func_7fb30a(void); // Incomplete
static void func_7fb335(void); // Incomplete
static void func_7fb360(void); // Incomplete
static void func_7fb375(void); // Incomplete
static void func_7fb38a(void); // Incomplete
static void func_7fb3a6(void); // Incomplete
static void func_7fb3c2(void); // Incomplete
static void func_7fb3de(void); // Incomplete
static void func_7fb3fa(void); // Incomplete
static void func_7fb41b(void); // Incomplete
static void func_7fb43c(void); // Incomplete
static void func_7fb45d(void); // Incomplete
static void func_7fb47e(void); // Incomplete
static void func_7fb49f(void); // Incomplete
static void func_7fb4e1(void); // Incomplete
static void func_7fb523(void); // Incomplete
static void func_7fb550(void); // Incomplete
static void func_7fb566(void); // Incomplete
static void func_7fb593(void); // Incomplete
static void func_7fb5a9(void); // Incomplete
static void func_7fb5eb(void); // Incomplete
static void func_7fb629(void); // Incomplete
static void func_7fb667(void); // Incomplete
static void func_7fb693(void); // Incomplete
static void func_7fb6ac(void); // Incomplete
static void func_7fb6c5(void); // Incomplete
static void func_7fb6de(void); // Incomplete
static void func_7fb6f7(void); // Incomplete
static void func_7fb710(void); // Incomplete
static void func_7fb729(void); // Incomplete
static void func_7fb742(void); // Incomplete
static void func_7fb75b(void); // Incomplete
static void func_7fb774(void); // Incomplete
static void func_7fb78d(void); // Incomplete
static void func_7fb7a6(void); // Incomplete
static void func_7fb7bf(void); // Incomplete
static void func_7fb7e2(void); // Incomplete
static void func_7fb805(void); // Incomplete
static void func_7fb828(void); // Incomplete
static void func_7fb846(void); // Incomplete
static void func_7fb88e(void); // Incomplete
static void func_7fb8a7(void); // Incomplete
static void func_7fb8c0(void); // Incomplete
static void func_7fb8d9(void); // Incomplete
static void func_7fb8f2(void); // Incomplete
static void func_7fb9cc(void); // Incomplete
static void func_7fb9e5(void); // Incomplete
static void func_7fb9fe(void); // Incomplete
static void func_7fba17(void); // Incomplete
static void func_7fba44(void); // Incomplete
static void func_7fba5d(void); // Incomplete
static void func_7fba86(void); // Incomplete
static void func_7fbaa9(void); // Incomplete
static void func_7fbb00(void); // Incomplete
static void func_7fbb79(void); // Incomplete
static void func_7fbbb0(void); // Incomplete
static void func_7fbbca(void); // Incomplete
static void func_7fbbe4(void); // Incomplete
static void func_7fbbfe(void); // Incomplete
static void func_7fbc3e(void); // Incomplete
static void func_7fbc71(void); // Incomplete
static void func_7fbc9a(void); // Incomplete
static void func_7fbcd7(void); // Incomplete
static void func_7fbd2a(void); // Incomplete
static void func_7fbd6c(void); // Incomplete
static void func_7fbd88(void); // Incomplete
static void func_7fbdb3(void); // Incomplete
static void func_7fbe34(void); // Incomplete
static void func_7fbe55(void); // Incomplete
static void func_7fbe7e(void); // Incomplete
static void func_7fbe85(void); // Incomplete
static void func_7fbed2(void); // Incomplete
static void func_7fbf1b(void); // Incomplete
static void func_7fbf28(void); // Incomplete
static void func_7fbf3b(void); // Incomplete
static void func_7fbf70(void); // Incomplete
static void func_7fbfaf(void); // Incomplete
static void func_7fbfc8(void); // Incomplete
static void func_7fbff4(void); // Incomplete
static void decompress(void); // Incomplete
static void highNybbleClear(void); // Incomplete
static void highNybbleSet(void); // Incomplete
static void compressionMode_lzss(void); // Incomplete
static void func_7fc1a3(void); // Incomplete
static void compressionMode_none(void); // Incomplete
static void func_7fc1e0(void); // Incomplete
static void func_7fc1f4(void); // Incomplete
static void func_7fc209(void); // Incomplete
static void func_7fc500(void); // Incomplete
static void func_7fc64f(void); // Incomplete
static void func_7fc678(void); // Incomplete

void decompExt(void) {}

// Address: _000f
// A: cutscene id
void showCutscene(uint8_t id) {}

// Address: _003d
static void initDecomp(void) {}

// Decompress
// ++$04f0/$d0: source
// ++$04f3/$d3: destination
static void decomp(void) {}

static void func_7f8000(void) {}

static void func_7f803a(void) {}

// Address: 7f/804b
static void cutscene_titleCredits(void) {}

static void func_7f8434(void) {}

static void func_7f846f(void) {}

static void func_7f8498(void) {}

static void func_7f84bb(void) {}

// Address: 7f/8516
static void cutscene_fallingMeteor(void) {}

static void func_7f8660(void) {}

static void func_7f867d(void) {}

// Address: 7f/8784
static void cutscene03(void) {}

// Address: 7f/8888
static void cutscene_flashRedShort(void) {}

// Address: 7f/8963
static void cutscene_flashRedLong(void) {}

static void func_7f8a4e(void) {}

// Address: 7f/8aa2
static void cutscene_lightningBolt(void) {}

// Address: 7f/8b80
static void cutscene_purpleSparklies(void) {}

static void func_7f8c09(void) {}

// Address: 7f/8c78
static void cutscene_endingCredits(void) {}

static void func_7f945d(void) {}

static void func_7f9465(void) {}

static void func_7f94a5(void) {}

static void func_7f95a1(void) {}

static void func_7f95ab(void) {}

static void func_7f95d9(void) {}

static void func_7f95ec(void) {}

static void func_7f95ff(void) {}

static void func_7f963a(void) {}

static void func_7f9679(void) {}

static void func_7f96b8(void) {}

static void func_7f96f9(void) {}

static void func_7f970e(void) {}

static void func_7f9753(void) {}

static void func_7f9780(void) {}

static void func_7f97ad(void) {}

static void func_7f97f8(void) {}

static void func_7f983b(void) {}

static void func_7f988a(void) {}

static void func_7f98d0(void) {}

static void func_7f9943(void) {}

static void func_7f99b6(void) {}

static void func_7f99ea(void) {}

static void func_7f9a1e(void) {}

static void func_7f9a29(void) {}

static void func_7f9a39(void) {}

static void func_7f9a49(void) {}

static void func_7f9a57(void) {}

static void func_7f9a65(void) {}

static void func_7f9a73(void) {}

static void func_7f9a81(void) {}

static void func_7f9a8f(void) {}

static void func_7f9a98(void) {}

static void func_7f9aa1(void) {}

static void func_7f9aa8(void) {}

static void func_7f9ab1(void) {}

static void func_7f9abd(void) {}

static void func_7f9ac9(void) {}

static void func_7f9ad9(void) {}

static void func_7f9ae4(void) {}

static void func_7f9af2(void) {}

static void func_7f9deb(void) {}

static void func_7f9f2c(void) {}

static void func_7fa244(void) {}

static void func_7fa3a0(void) {}

static void func_7fa3b6(void) {}

static void func_7fa50e(void) {}

static void func_7fa527(void) {}

static void func_7fa538(void) {}

static void func_7fa549(void) {}

static void func_7fa554(void) {}

static void func_7fa562(void) {}

static void func_7fa570(void) {}

static void func_7fa797(void) {}

static void func_7fa811(void) {}

static void func_7fa8c6(void) {}

static void func_7fa963(void) {}

static void func_7faafc(void) {}

static void func_7fab3b(void) {}

static void func_7fab7a(void) {}

static void func_7fac2a(void) {}

static void func_7fac54(void) {}

static void func_7fac78(void) {}

static void func_7facab(void) {}

static void func_7faccc(void) {}

static void func_7fad0d(void) {}

static void func_7fad23(void) {}

static void func_7fae01(void) {}

static void func_7fae2d(void) {}

static void func_7fae37(void) {}

static void func_7fae70(void) {}

static void func_7faebc(void) {}

static void func_7faf08(void) {}

static void func_7faf81(void) {}

static void func_7fafa1(void) {}

static void func_7fafae(void) {}

static void func_7fafc1(void) {}

static void func_7fafed(void) {}

static void func_7faff3(void) {}

static void func_7faff9(void) {}

static void func_7fafff(void) {}

static void func_7fb035(void) {}

static void func_7fb046(void) {}

static void func_7fb067(void) {}

static void func_7fb08a(void) {}

static void func_7fb0ad(void) {}

static void func_7fb124(void) {}

static void func_7fb19f(void) {}

static void func_7fb1fd(void) {}

static void func_7fb21d(void) {}

static void func_7fb273(void) {}

static void func_7fb29e(void) {}

static void func_7fb30a(void) {}

static void func_7fb335(void) {}

static void func_7fb360(void) {}

static void func_7fb375(void) {}

static void func_7fb38a(void) {}

static void func_7fb3a6(void) {}

static void func_7fb3c2(void) {}

static void func_7fb3de(void) {}

static void func_7fb3fa(void) {}

static void func_7fb41b(void) {}

static void func_7fb43c(void) {}

static void func_7fb45d(void) {}

static void func_7fb47e(void) {}

static void func_7fb49f(void) {}

static void func_7fb4e1(void) {}

static void func_7fb523(void) {}

static void func_7fb550(void) {}

static void func_7fb566(void) {}

static void func_7fb593(void) {}

static void func_7fb5a9(void) {}

static void func_7fb5eb(void) {}

static void func_7fb629(void) {}

static void func_7fb667(void) {}

static void func_7fb693(void) {}

static void func_7fb6ac(void) {}

static void func_7fb6c5(void) {}

static void func_7fb6de(void) {}

static void func_7fb6f7(void) {}

static void func_7fb710(void) {}

static void func_7fb729(void) {}

static void func_7fb742(void) {}

static void func_7fb75b(void) {}

static void func_7fb774(void) {}

static void func_7fb78d(void) {}

static void func_7fb7a6(void) {}

static void func_7fb7bf(void) {}

static void func_7fb7e2(void) {}

static void func_7fb805(void) {}

static void func_7fb828(void) {}

static void func_7fb846(void) {}

static void func_7fb88e(void) {}

static void func_7fb8a7(void) {}

static void func_7fb8c0(void) {}

static void func_7fb8d9(void) {}

static void func_7fb8f2(void) {}

static void func_7fb9cc(void) {}

static void func_7fb9e5(void) {}

static void func_7fb9fe(void) {}

static void func_7fba17(void) {}

static void func_7fba44(void) {}

static void func_7fba5d(void) {}

static void func_7fba86(void) {}

static void func_7fbaa9(void) {}

static void func_7fbb00(void) {}

static void func_7fbb79(void) {}

static void func_7fbbb0(void) {}

static void func_7fbbca(void) {}

static void func_7fbbe4(void) {}

static void func_7fbbfe(void) {}

static void func_7fbc3e(void) {}

static void func_7fbc71(void) {}

static void func_7fbc9a(void) {}

static void func_7fbcd7(void) {}

static void func_7fbd2a(void) {}

static void func_7fbd6c(void) {}

static void func_7fbd88(void) {}

static void func_7fbdb3(void) {}

static void func_7fbe34(void) {}

static void func_7fbe55(void) {}

static void func_7fbe7e(void) {}

static void func_7fbe85(void) {}

static void func_7fbed2(void) {}

static void func_7fbf1b(void) {}

static void func_7fbf28(void) {}

static void func_7fbf3b(void) {}

static void func_7fbf70(void) {}

static void func_7fbfaf(void) {}

static void func_7fbfc8(void) {}

static void func_7fbff4(void) {}

// Address: 7f/c00d
static void decompress(void) {}

// Address: 7f/c05d
static void highNybbleClear(void) {}

// Address: 7f/c0a1
static void highNybbleSet(void) {}

// Address: 7f/c0f0
static void compressionMode_lzss(void) {}

static void func_7fc1a3(void) {}

// Address: 7f/c1cc
static void compressionMode_none(void) {}

static void func_7fc1e0(void) {}

static void func_7fc1f4(void) {}

static void func_7fc209(void) {}

static void func_7fc500(void) {}

static void func_7fc64f(void) {}

static void func_7fc678(void) {}