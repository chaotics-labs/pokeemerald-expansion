# How to use the Outfit System

The outfit system lets the player switch between different visual appearances (overworld sprites, trainer pics, map icons) during gameplay. Outfits can be unlocked via scripts, purchased from an outfit shop, and selected from a dedicated menu.

## Contents
1. [Key files](#key-files)
2. [How outfits work](#how-outfits-work)
3. [Adding a new outfit](#adding-a-new-outfit)
    - [1. Define the constant](#1-define-the-constant)
    - [2. Add the outfit data](#2-add-the-outfit-data)
    - [3. Provide the graphics](#3-provide-the-graphics)
4. [Scripting commands](#scripting-commands)
    - [Core macros](#core-macros)
    - [Shortcut macros](#shortcut-macros)
    - [Conditional macros](#conditional-macros)
    - [Outfit shop](#outfit-shop)
5. [C API reference](#c-api-reference)
6. [The outfit menu](#the-outfit-menu)
7. [Example: full walkthrough](#example-full-walkthrough)

---

## Key files

| File | Purpose |
|------|---------|
| `include/constants/outfits.h` | Outfit ID constants and script command modes |
| `src/data/outfit_tables.h` | Outfit data array (`gOutfits[]`) — name, sprites, icons, prices |
| `include/data.h` | `struct Outfit` definition |
| `src/outfit_menu.c` | Outfit selection menu logic |
| `include/outfit_menu.h` | Public API for outfit functions |
| `asm/macros/event.inc` | Script macros for outfit commands |
| `src/scrcmd.c` | Script command implementations |
| `src/field_player_avatar.c` | `GetPlayerAvatarGraphicsIdByOutfitStateIdAndGender` |
| `src/shop.c` | Outfit shop (`CreateOutfitShopMenu`) |

---

## How outfits work

Each outfit is a constant ID defined in `include/constants/outfits.h`. The data for each outfit lives in the `gOutfits[]` array in `src/data/outfit_tables.h`.

The `struct Outfit` (defined in `include/data.h`) contains:

```c
struct Outfit
{
    u8 isHidden:1;                                    // Won't appear in the menu if locked
    u32 prices[GENDER_COUNT];                         // Purchase cost per gender
    const u8 *name;                                   // Display name
    const u8 *desc;                                   // Description text
    u16 trainerPics[GENDER_COUNT][2];                 // [gender][front/back] trainer pic IDs
    u16 avatarGfxIds[PLAYER_AVATAR_STATE_COUNT][GENDER_COUNT]; // Overworld sprites per state
    const void *iconsRM[GENDER_COUNT];                // Region map head icons per gender
    const void *iconsFP;                              // Frontier pass head icons (both genders in one sprite)
};
```

Unlock state is stored as a bitfield in the save data (`gSaveBlock2Ptr->outfits[]`), and the currently worn outfit ID is stored in `gSaveBlock2Ptr->currOutfitId`.

`OUTFIT_NONE` (0) is a special empty slot — the system defaults to `DEFAULT_OUTFIT` if the current outfit is `OUTFIT_NONE`.

---

## Adding a new outfit

### 1. Define the constant

In `include/constants/outfits.h`, add your new outfit ID and update `OUTFIT_COUNT` and `OUTFIT_END`:

```diff
 #define OUTFIT_NONE 0
 #define OUTFIT_USUAL_GREEN 1
 #define OUTFIT_UNUSUAL_RED 2
-#define OUTFIT_COUNT 3
+#define OUTFIT_KANTO_CLASSIC 3
+#define OUTFIT_COUNT 4

 // inclusive
 #define OUTFIT_BEGIN OUTFIT_USUAL_GREEN
-#define OUTFIT_END   OUTFIT_UNUSUAL_RED
+#define OUTFIT_END   OUTFIT_KANTO_CLASSIC
```

### 2. Add the outfit data

In `src/data/outfit_tables.h`, add an entry in the `gOutfits[]` array. Follow the existing pattern:

```c
[OUTFIT_KANTO_CLASSIC] = {
    // If TRUE, this outfit won't show in the menu when locked.
    .isHidden = FALSE,

    // Purchase price per gender: { male_price, female_price }
    .prices = { 500, 500 },

    // Display name and description
    .name = COMPOUND_STRING("KANTO CLASSIC"),
    .desc = COMPOUND_STRING("A throwback to the Kanto\nregion."),

    // Trainer front and back pics per gender
    // (see include/constants/trainers.h for TRAINER_PIC_* constants)
    .trainerPics = {
        [MALE]   = { TRAINER_PIC_FRONT_RED, TRAINER_PIC_BACK_RED },
        [FEMALE] = { TRAINER_PIC_FRONT_LEAF, TRAINER_PIC_BACK_LEAF },
    },

    // Overworld sprites for each avatar state
    // (see include/constants/event_objects.h for OBJ_EVENT_GFX_* constants)
    .avatarGfxIds = {
        [PLAYER_AVATAR_STATE_NORMAL]     = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_NORMAL,    [FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_NORMAL },
        [PLAYER_AVATAR_STATE_MACH_BIKE]  = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_ACRO_BIKE, [FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_ACRO_BIKE },
        [PLAYER_AVATAR_STATE_ACRO_BIKE]  = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_ACRO_BIKE, [FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_ACRO_BIKE },
        [PLAYER_AVATAR_STATE_SURFING]    = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_SURFING,   [FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_SURFING },
        [PLAYER_AVATAR_STATE_UNDERWATER] = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_UNDERWATER,[FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_UNDERWATER },
        [PLAYER_AVATAR_STATE_FIELD_MOVE] = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_FIELD_MOVE,[FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_FIELD_MOVE },
        [PLAYER_AVATAR_STATE_FISHING]    = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_FISHING,   [FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_FISHING },
        [PLAYER_AVATAR_STATE_WATERING]   = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_WATERING,  [FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_WATERING },
        [PLAYER_AVATAR_STATE_VSSEEKER]   = { [MALE] = OBJ_EVENT_GFX_KANTO_BRENDAN_FIELD_MOVE,[FEMALE] = OBJ_EVENT_GFX_KANTO_MAY_FIELD_MOVE },
    },

    // Region map head icons (one per gender)
    .iconsRM = { sRegionMapPlayerIcon_KantoBrendanGfx, sRegionMapPlayerIcon_KantoMayGfx },

    // Frontier pass head icons (both genders in one sprite sheet)
    .iconsFP = sFrontierPassPlayerIcons_KantoBrendanMay_Gfx,
},
```

> **Note:** If you're building without `MODERN`, you'll need to declare the name/description strings as separate `static const u8` arrays and wrap both variants in `#if MODERN == 1` / `#else` guards, as the existing outfits do.

### 3. Provide the graphics

You'll need to supply the following graphics for your outfit:

- **Overworld sprites** — One for each avatar state listed in `.avatarGfxIds`. These must be registered as object event graphics in the usual way (see the object event graphics system). At minimum you need: normal, acro bike, surfing, underwater, field move, fishing, watering, and VS Seeker sprites for both genders.

- **Trainer front and back pics** — Referenced by the `TRAINER_PIC_*` constants. See the [trainer front pic tutorial](how_to_trainer_front_pic.md) and [trainer back pic tutorial](how_to_trainer_back_pic.md) for how to add these.

- **Region map icons** — 16×16 4bpp head icons, one per gender. Declare as `INCBIN_U16` in `src/data/outfit_tables.h`.

- **Frontier pass icons** — A single sprite sheet containing both genders' head icons. Declare as `INCBIN_U8` in `src/data/outfit_tables.h`.

---

## Scripting commands

All outfit script macros are defined in `asm/macros/event.inc`.

### Core macros

These are the low-level macros that the script commands map to:

| Macro | Arguments | Description |
|-------|-----------|-------------|
| `toggleoutfit` | `outfitId, type` | Unlocks (`OUTFIT_TOGGLE_UNLOCK`) or locks (`OUTFIT_TOGGLE_LOCK`) an outfit |
| `getoutfitstatus` | `outfitId, data` | Sets `VAR_RESULT`: `OUTFIT_CHECK_FLAG` checks unlock state, `OUTFIT_CHECK_USED` checks if currently worn |
| `bufferoutfitstr` | `stringVarId, outfitId, type` | Buffers outfit name (`OUTFIT_BUFFER_NAME`) or description (`OUTFIT_BUFFER_DESC`) to a string var |
| `pokemartoutfit` | `products` | Opens an outfit shop with the given product list |
| `setoutfitgfxintovar` | `var, state` | Stores the current outfit's OBJ_EVENT_GFX ID for the given avatar state into a variable |

### Shortcut macros

Convenience wrappers around the core macros:

| Macro | Arguments | Equivalent to |
|-------|-----------|---------------|
| `unlockoutfit` | `outfitId` | `toggleoutfit outfitId, OUTFIT_TOGGLE_UNLOCK` |
| `lockoutfit` | `outfitId` | `toggleoutfit outfitId, OUTFIT_TOGGLE_LOCK` |
| `checkoutfitflag` | `outfitId` | `getoutfitstatus outfitId, OUTFIT_CHECK_FLAG` |
| `iswearingoutfit` | `outfitId` | `getoutfitstatus outfitId, OUTFIT_CHECK_USED` |
| `bufferoutfitname` | `stringVarId, outfitId` | `bufferoutfitstr stringVarId, outfitId, OUTFIT_BUFFER_NAME` |
| `bufferoutfitdesc` | `stringVarId, outfitId` | `bufferoutfitstr stringVarId, outfitId, OUTFIT_BUFFER_DESC` |

### Conditional macros

Jump/call helpers that check outfit state:

| Macro | Arguments | Description |
|-------|-----------|-------------|
| `call_if_outfitunlocked` | `outfit, dest` | Calls `dest` if the outfit is unlocked |
| `call_if_outfitlocked` | `outfit, dest` | Calls `dest` if the outfit is locked |
| `call_if_wearoutfit` | `outfit, dest` | Calls `dest` if the player is currently wearing the outfit |
| `call_if_notwearoutfit` | `outfit, dest` | Calls `dest` if the player is **not** currently wearing the outfit |

### Outfit shop

To create an outfit shop, define a product list and use `pokemartoutfit`:

```asm
    .align 2
OutfitShop_Products:
    .2byte OUTFIT_UNUSUAL_RED
    .2byte OUTFIT_KANTO_CLASSIC
    .2byte OUTFIT_NONE  @ terminator

MyOutfitShopScript::
    lock
    faceplayer
    msgbox Text_WelcomeToOutfitShop, MSGBOX_DEFAULT
    pokemartoutfit OutfitShop_Products
    release
    end
```

Each outfit's price is defined in its `.prices` field in the outfit data. The price used depends on the player's gender.

---

## C API reference

These functions are declared in `include/outfit_menu.h`:

| Function | Description |
|----------|-------------|
| `OpenOutfitMenu(MainCallback retCB)` | Opens the outfit selection UI; `retCB` is called when the menu closes |
| `Task_OpenOutfitMenu(u8 taskId)` | Task wrapper for opening the menu from the overworld (waits for fade) |
| `UnlockOutfit(u16 id)` | Sets the unlock bit for the given outfit |
| `LockOutfit(u16 id)` | Clears the unlock bit |
| `ToggleOutfit(u16 id)` | Flips the unlock bit |
| `GetOutfitStatus(u16 id)` | Returns `TRUE` if the outfit is unlocked |
| `IsPlayerWearingOutfit(u16 id)` | Returns `TRUE` if the outfit is currently equipped |
| `GetOutfitPrice(u16 id)` | Returns the price for the player's current gender |
| `BufferOutfitStrings(u8 *dest, u8 outfitId, u8 dataType)` | Copies the outfit's name or description into `dest` |
| `GetPlayerTrainerPicIdByOutfitGenderType(u32 outfitId, u32 gender, bool32 type)` | Returns the trainer pic ID (front if `type=0`, back if `type=1`) |
| `GetPlayerHeadGfxOrPal(u8 which, bool32 isFP)` | Returns the region map or frontier pass icon graphics/palette for the current outfit |

From `include/field_player_avatar.h`:

| Function | Description |
|----------|-------------|
| `GetPlayerAvatarGraphicsIdByOutfitStateIdAndGender(u8 outfit, u8 state, u8 gender)` | Returns the `OBJ_EVENT_GFX_*` ID for the given outfit, avatar state, and gender |

---

## The outfit menu

The outfit menu (`src/outfit_menu.c`) is a grid-based UI that displays:

- A scrollable list of outfit overworld sprites on the right side
- The selected outfit's front and back trainer pics on the left
- The outfit name and description at the bottom

**Behavior:**
- Hidden outfits (`.isHidden = TRUE`) are not shown in the list when locked
- Locked outfits appear grayed out (palette tinted to grayscale) and show `???` for name/description
- Pressing **A** equips the selected outfit (only when the player is on foot)
- Changing outfits is blocked while cycling, surfing, or diving — a contextual error message is shown
- Pressing **B** or **Start** closes the menu

---

## Example: full walkthrough

Here's a complete example of unlocking an outfit via an NPC script:

```asm
EventScript_OutfitGiver::
    lock
    faceplayer
    checkoutfitflag OUTFIT_UNUSUAL_RED
    goto_if_eq VAR_RESULT, TRUE, EventScript_OutfitGiver_AlreadyHave
    msgbox Text_HereIsAnOutfit, MSGBOX_DEFAULT
    unlockoutfit OUTFIT_UNUSUAL_RED
    bufferoutfitname STR_VAR_1, OUTFIT_UNUSUAL_RED
    msgbox Text_ReceivedOutfit, MSGBOX_DEFAULT
    release
    end

EventScript_OutfitGiver_AlreadyHave::
    msgbox Text_AlreadyHaveOutfit, MSGBOX_DEFAULT
    release
    end

Text_HereIsAnOutfit:
    .string "Here, take this outfit!$"

Text_ReceivedOutfit:
    .string "{PLAYER} received the\n{STR_VAR_1} outfit!$"

Text_AlreadyHaveOutfit:
    .string "You already have that outfit.$"
```
