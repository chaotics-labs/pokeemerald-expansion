#include "constants/global.h"
#include "constants/event_objects.h"

#if MODERN == 0
static const u8 sText_OutfitName_UsualGreen[] = _("USUAL GREEN");
static const u8 sText_OutfitDesc_UsualGreen[] = _(
    "The usual, but basic OUTFIT.");

static const u8 sText_OutfitName_UnusualRed[] = _("UNUSUAL RED");
static const u8 sText_OutfitDesc_UnusualRed[] = _(
    "Rather unusual, but still basic\nOUTFIT.");
#endif

static const u16 sRegionMapPlayerIcon_BrendanGfx[] = INCBIN_U16("graphics/pokenav/region_map/brendan_icon.4bpp");

static const u16 sRegionMapPlayerIcon_RSBrendanGfx[] = INCBIN_U16("graphics/pokenav/region_map/rs_brendan_icon.4bpp");

static const u16 sRegionMapPlayerIcon_MayGfx[] = INCBIN_U16("graphics/pokenav/region_map/may_icon.4bpp");

static const u16 sRegionMapPlayerIcon_RSMayGfx[] = INCBIN_U16("graphics/pokenav/region_map/rs_may_icon.4bpp");

//! TODO: Should the gfx here be seperated?

static const u8 sFrontierPassPlayerIcons_BrendanMay_Gfx[] = INCBIN_U8("graphics/frontier_pass/map_heads.4bpp");

static const u8 sFrontierPassPlayerIcons_RSBrendanMay_Gfx[] = INCBIN_U8("graphics/frontier_pass/rs_map_heads.4bpp");

#define REGION_MAP_GFX(m, f) { sRegionMapPlayerIcon_ ## m ## Gfx, sRegionMapPlayerIcon_ ## f ## Gfx }

// bandaids to avoid adding unnecessary merge conflicts
// remove these if you have them added/renamed yourself.
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_NORMAL     OBJ_EVENT_GFX_LINK_RS_BRENDAN
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_ACRO_BIKE  OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_SURFING    OBJ_EVENT_GFX_BRENDAN_SURFING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_UNDERWATER OBJ_EVENT_GFX_BRENDAN_UNDERWATER
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FISHING    OBJ_EVENT_GFX_BRENDAN_FISHING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_WATERING   OBJ_EVENT_GFX_BRENDAN_WATERING
#define OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_DECORATING OBJ_EVENT_GFX_BRENDAN_DECORATING

#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_NORMAL     OBJ_EVENT_GFX_LINK_RS_MAY
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_ACRO_BIKE  OBJ_EVENT_GFX_MAY_ACRO_BIKE
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_SURFING    OBJ_EVENT_GFX_MAY_SURFING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_UNDERWATER OBJ_EVENT_GFX_MAY_UNDERWATER
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE OBJ_EVENT_GFX_MAY_FIELD_MOVE
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_FISHING    OBJ_EVENT_GFX_MAY_FISHING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_WATERING   OBJ_EVENT_GFX_MAY_WATERING
#define OBJ_EVENT_GFX_OUTFIT_RS_MAY_DECORATING OBJ_EVENT_GFX_MAY_DECORATING

const struct Outfit gOutfits[OUTFIT_COUNT] =
{
    [OUTFIT_NONE] = {
        .isHidden = TRUE
    },
    [OUTFIT_USUAL_GREEN] = {
        //! DESC: if sets to TRUE, it will not be shown in the OUTFIT menu if it's locked.
        .isHidden = FALSE,

        //! DESC: prices for purchasing them.
        .prices = { 0, 0 },

        //! agbcc doesnt like COMPOUND_STRING on my end
        //! DESC: outfit's name
        #if MODERN == 1
        .name = COMPOUND_STRING("USUAL GREEN"),
        #else
        .name = sText_OutfitName_UsualGreen,
        #endif

        //! DESC: outfit's description
        #if MODERN == 1
        .desc = COMPOUND_STRING("The usual, but basic OUTFIT."),
        #else
        .desc = sText_OutfitDesc_UsualGreen,
        #endif

        //! DESC: trainer front & back pic index
        //! (see include/constants/trainers.h)
        .trainerPics = {
            [MALE] =   { TRAINER_PIC_FRONT_BRENDAN, TRAINER_PIC_BACK_BRENDAN, },
            [FEMALE] = { TRAINER_PIC_FRONT_MAY, TRAINER_PIC_BACK_MAY, },
        },

        //! DESC: overworld avatars indexed by [state][gender].
        //! All states from PLAYER_AVATAR_STATE_NORMAL through PLAYER_AVATAR_STATE_VSSEEKER.
        //! (see include/global.fieldmap.h and include/constants/event_objects.h)
        .avatarGfxIds = {
            [PLAYER_AVATAR_STATE_NORMAL] =     { [MALE] = OBJ_EVENT_GFX_BRENDAN_NORMAL,     [FEMALE] = OBJ_EVENT_GFX_MAY_NORMAL },
            [PLAYER_AVATAR_STATE_MACH_BIKE] =  { [MALE] = OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE,  [FEMALE] = OBJ_EVENT_GFX_MAY_ACRO_BIKE },
            [PLAYER_AVATAR_STATE_ACRO_BIKE] =  { [MALE] = OBJ_EVENT_GFX_BRENDAN_ACRO_BIKE,  [FEMALE] = OBJ_EVENT_GFX_MAY_ACRO_BIKE },
            [PLAYER_AVATAR_STATE_SURFING] =    { [MALE] = OBJ_EVENT_GFX_BRENDAN_SURFING,     [FEMALE] = OBJ_EVENT_GFX_MAY_SURFING },
            [PLAYER_AVATAR_STATE_UNDERWATER] = { [MALE] = OBJ_EVENT_GFX_BRENDAN_UNDERWATER,  [FEMALE] = OBJ_EVENT_GFX_MAY_UNDERWATER },
            [PLAYER_AVATAR_STATE_FIELD_MOVE] = { [MALE] = OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE,  [FEMALE] = OBJ_EVENT_GFX_MAY_FIELD_MOVE },
            [PLAYER_AVATAR_STATE_FISHING] =    { [MALE] = OBJ_EVENT_GFX_BRENDAN_FISHING,     [FEMALE] = OBJ_EVENT_GFX_MAY_FISHING },
            [PLAYER_AVATAR_STATE_WATERING] =   { [MALE] = OBJ_EVENT_GFX_BRENDAN_WATERING,    [FEMALE] = OBJ_EVENT_GFX_MAY_WATERING },
            [PLAYER_AVATAR_STATE_VSSEEKER] =   { [MALE] = OBJ_EVENT_GFX_BRENDAN_FIELD_MOVE,  [FEMALE] = OBJ_EVENT_GFX_MAY_FIELD_MOVE },
        },

        //! DESC: head icons gfx&pal for region map
        .iconsRM = { sRegionMapPlayerIcon_BrendanGfx, sRegionMapPlayerIcon_MayGfx },

        //! DESC: head icons gfx&pal for frontier pass
        //! note that frontier pass needs to be in one sprite instead of two,
        //! unlike region map. (probably should split them tbh)
        .iconsFP = sFrontierPassPlayerIcons_BrendanMay_Gfx,
    },
    [OUTFIT_UNUSUAL_RED] = {
        .isHidden = FALSE,
        .prices = { 200, 500 },
        #if MODERN == 1
        .name = COMPOUND_STRING("UNUSUAL RED"),
        .desc = COMPOUND_STRING("Rather unusual, but still basic\nOUTFIT."),
        #else
        .name = sText_OutfitName_UnusualRed,
        .desc = sText_OutfitDesc_UnusualRed,
        #endif
        .trainerPics = {
            [MALE]   = {TRAINER_PIC_FRONT_RS_BRENDAN, TRAINER_PIC_BACK_RUBY_SAPPHIRE_BRENDAN},
            [FEMALE] = {TRAINER_PIC_FRONT_RS_MAY, TRAINER_PIC_BACK_RUBY_SAPPHIRE_MAY}
        },
        .avatarGfxIds = {
            [PLAYER_AVATAR_STATE_NORMAL] =     { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_NORMAL,     [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_NORMAL },
            [PLAYER_AVATAR_STATE_MACH_BIKE] =  { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_ACRO_BIKE,  [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_ACRO_BIKE },
            [PLAYER_AVATAR_STATE_ACRO_BIKE] =  { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_ACRO_BIKE,  [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_ACRO_BIKE },
            [PLAYER_AVATAR_STATE_SURFING] =    { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_SURFING,     [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_SURFING },
            [PLAYER_AVATAR_STATE_UNDERWATER] = { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_UNDERWATER,  [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_UNDERWATER },
            [PLAYER_AVATAR_STATE_FIELD_MOVE] = { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE,  [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE },
            [PLAYER_AVATAR_STATE_FISHING] =    { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FISHING,     [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_FISHING },
            [PLAYER_AVATAR_STATE_WATERING] =   { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_WATERING,    [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_WATERING },
            [PLAYER_AVATAR_STATE_VSSEEKER] =   { [MALE] = OBJ_EVENT_GFX_OUTFIT_RS_BRENDAN_FIELD_MOVE,  [FEMALE] = OBJ_EVENT_GFX_OUTFIT_RS_MAY_FIELD_MOVE },
        },
        .iconsRM = { sRegionMapPlayerIcon_RSBrendanGfx, sRegionMapPlayerIcon_RSMayGfx },
        .iconsFP = sFrontierPassPlayerIcons_RSBrendanMay_Gfx,
    },
};
