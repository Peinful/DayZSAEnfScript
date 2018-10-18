enum ERPCs
{
	PB_START = -1,
	PB_END = -2,
	PB_SINGLEUSE_START = -3,
	PB_SINGLEUSE_END = -4,
	RPC_SYNC_ITEM_VAR = 0,
	RPC_SYNC_STAT,
	RPC_WRITE_NOTE,
	RPC_SYNC_DISPLAY_STATUS,
	RPC_ON_SET_CAPTIVE,
	RPC_SYNC_SCENE_OBJECT,
	RPC_READ_A_BOOK,
	RPC_USER_ACTION_PROMPT_SYNCH,
	RPC_USER_ACTION_MESSAGE,
	RPC_ITEM_DIAG,
	RPC_ITEM_DIAG_CLOSE,
	RPC_SET_OBJECT_POSITION,
	RPC_USER_ACTION_MESSAGES,
	RPC_PLAYER_SYMPTOM_ON,
	RPC_PLAYER_SYMPTOM_OFF,
	RPC_STAMINA,
	RPC_DAMAGE_VALUE_SYNC,
	RPC_DEBUG_MONITOR_FLT,
	RPC_DEBUG_MONITOR_STR,
	RPC_USER_ACTION_PROMPT_PROGRESS,
	RPC_USER_ACTION_PROMPT_CLEAN,
	RPC_DISABLE_MODIFIERS,
	RPC_KILL_PLAYER,
	RPC_ENABLE_INVINCIBILITY,
	RPC_ITEM_DEBUG_ACTIONS,
	RPC_ENABLE_QUICK_RESTRAIN,
	RPC_LOG_PLAYER_STATS,
	RPC_EM_PLUG_CHANGED,
	RPC_BS_SKINNED_STATE,
	RPC_GARDEN_SLOTS,
	RPC_PLANT_STATE,
	RPC_PLANT_STATE_INDEX,
	RPC_PLANT_CROPS,
	RPC_PLANT_INFESTATION,
	RPC_PLANT_PESTICIDE,
	RPC_PLANT_SLOT,
	RPC_PLANT_GARDEN,
	RPC_TRAP_VICTIM,
	DEV_RPC_SPAWN_ITEM_ON_GROUND,
	DEV_RPC_SPAWN_ITEM_ON_CURSOR,
	DEV_RPC_SPAWN_ITEM_IN_INVENTORY,
	DEV_RPC_SPAWN_ITEM_AS_ATTACHMENT,
	DEV_RPC_CLEAR_INV,
	DEV_RPC_TELEPORT,
	DEV_RPC_SET_PLAYER_DIRECTION,
	DEV_RPC_SEND_SERVER_LOG,
	DEV_RPC_STATS_DATA,
	DEV_RPC_MODS_DATA,
	DEV_RPC_MODS_ACTIVATE,
	DEV_RPC_MODS_DEACTIVATE,
	DEV_RPC_MODS_LOCK,
	DEV_RPC_AGENTS_DATA,
	DEV_RPC_CREATE_SCENE_OBJECT,
	DEV_RPC_SCENE_LOAD,
	DEV_RPC_UNLIMITED_AMMO,
	DEV_RPC_DISABLE_BLOODLOOS,
	DEV_RPC_MELEE_BLOCK_STANCE,
	DEV_RPC_MELEE_FIGHT,
	DEV_STATS_UPDATE,
	DEV_MODS_UPDATE,
	DEV_AGENTS_UPDATE,
	DEV_RPC_PLUGIN_DZCREATURE_DEBUG,
	DEV_REQUEST_PLAYER_DEBUG,
	DEV_PLAYER_DEBUG_DATA,
	DEV_GO_UNCONSCIOUS,
	DEV_GO_UNCONSCIOUS_DELAYED,
	RPC_PLAYER_SYMPTOMS_DEBUG,
	RPC_SOFT_SKILLS_TOGGLE_STATE,
	RPC_SOFT_SKILLS_DEBUG_WINDOW,
	RPC_SOFT_SKILLS_TOGGLE_MODEL,
	RPC_SOFT_SKILLS_SPECIALTY_SYNC,
	RPC_SOFT_SKILLS_STATS_SYNC,
	RPC_SOFT_SKILLS_SET_SPECIALTY,
	RPC_SOFT_SKILLS_PRINT_DEBUG,
	RPC_GUN_PARTICLES_TOGGLE,
	RPC_PLAYER_SYMPTOMS_EXIT,
	RPC_PLAYER_SYMPTOMS_DEBUG_ON,
	RPC_CRAFTING_DEBUG,
	RPC_CRAFTING_INVENTORY_INSTANT,
	RPC_LIFESPAN_BLOODY_HANDS,
	RPC_LIFESPAN_PLAYTIME_UPDATE,
	RPC_INIT_SET_QUICKBAR,
	RPC_READ_NOTE,
	RPC_SYNC_EVENT,
	RPC_CHARACTER_EQUIPPED,
	DEV_SIMULATE_NULL_POINTER,
	DEV_SIMULATE_DIVISION_BY_ZERO,
	DEV_SIMULATE_INFINITE_LOOP,
	DEV_SIMULATE_ERROR_FUNCTION,
	DEV_ACTIVATE_ALL_BS,
	DEV_ACTIVATE_BS,

#ifdef DEVELOPER
	RPC_DAYZPLAYER_DEBUGSERVERWALK,
#endif
}