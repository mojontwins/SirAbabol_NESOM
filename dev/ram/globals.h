// MT MK3 OM v0.3 [Sir Ababol NES_OM]
// Copyleft 2017, 2018 by The Mojon Twins

// ----------------------------------------------------------
// System 
// ----------------------------------------------------------
#ifdef SPECCY
	struct sp_UDK keys;
	void *joyfunc;
	int key_jump;

	struct sp_Rect spritesClipValues = { SCR_Y, SCR_X, 20, 30 };
	struct sp_Rect *spritesClip;
	struct sp_Rect fsRect = {0, 0, 24, 32};

	struct sp_SS *sp_sw [SW_SPRITES_ALL];
	unsigned char *spr_next [SW_SPRITES_ALL];
	unsigned char *spr_cur [SW_SPRITES_ALL];
#endif

#ifdef CPC
	#define KEY_LEFT 		0
	#define KEY_RIGHT		1
	#define KEY_DOWN 		2
	#define KEY_BUTTON_B	3
	#define KEY_BUTTON_A	4
	#define KEY_UP  		5
	#define KEY_ENTER		6
	#define KEY_ESC			7
	
	typedef struct sprite {
		int sp0;					// 0
		int sp1; 					// 2
		int coord0;
		int coord1;
		unsigned char cx, cy; 		// 8 9
		unsigned char ox, oy;		// 10 11
		unsigned char move;
		unsigned char move1;
	} SPR;

	unsigned char *spr_next [SW_SPRITES_ALL];

	//SPR sp_sw [SW_SPRITES_ALL];
	SPR sp_sw [SW_SPRITES_ALL] @ BASE_SPRITES;
#endif

unsigned char spr_on [SW_SPRITES_ALL];
unsigned char spr_x [SW_SPRITES_ALL], spr_y [SW_SPRITES_ALL];
unsigned char spr_idx;

// ----------------------------------------------------------
// General 
// ----------------------------------------------------------
unsigned char gpit, gpjt;
unsigned int gpint;
signed char rds;
signed int rdsint;
unsigned char rda, rdb, rdc, rdd, rde, rdf, rdi;
unsigned char rdx, rdy, rdt, rdct, rdxx, rdyy, rdyx, rdch;
unsigned char *gp_gen;
unsigned char *gp_int;
unsigned char pad0, pad, pad_this_frame;

// ----------------------------------------------------------
// Collision 
// ----------------------------------------------------------
unsigned char cx1, cx2, cy1, cy2, at1, at2;

// ----------------------------------------------------------
// Current level, screen, etc
// ----------------------------------------------------------
unsigned char level;
unsigned char *c_level;
unsigned char n_pant, on_pant;
unsigned char half_life, frame_counter, hl_proc;
unsigned char do_game, first_time;

// ----------------------------------------------------------
// Map stuff
// ----------------------------------------------------------
unsigned char *gp_map;

#ifdef SPECCY
#ifdef MODE_128K
	unsigned char scr_attr [160];
#else
		unsigned char scr_attr [160] @ (FREEPOOL + 160);
	#endif
	unsigned char scr_buff [160] @ FREEPOOL;
#endif
#ifdef CPC
	// Stuff this in gaps in VRAM
	// unsigned char scr_attr [160];
	// unsigned char scr_buff [160];
	unsigned char scr_attr [160] @ FREEPOOL;
	unsigned char scr_buff [160] @ (FREEPOOL + 160);
#endif

// ----------------------------------------------------------
// Player
// ----------------------------------------------------------
#ifdef ENEMIES_CAN_DIE
unsigned char pbodycount, opbodycount;
#endif
unsigned char plife, oplife, pobjs, opobjs, pkeys, opkeys;
unsigned char pstars, opstars;
#ifdef AMMO_MAX
unsigned char pammo, opammo;
#endif
unsigned char evil_tile_hit;
unsigned char pkilled;
unsigned char pemmeralds;
unsigned char pinv;
unsigned char guay_ct, use_ct, no_ct;

unsigned char prx, pry;
signed int px, py;
signed char pvx;
signed int pvy;

#ifdef PLAYER_JUMPS
	unsigned char pj, pctj, pthrust, pjb;
	unsigned char pjustjumped;
#endif

#ifdef PLAYER_DOUBLE_JUMP
	unsigned char njumps;
#endif

#ifdef PLAYER_BUTT
	unsigned char pbutt;
#endif

#ifdef PLAYER_PUSH_BOXES_ANIMATE
	unsigned char ppushing;
#endif

unsigned char pfiring;
unsigned char phit, pflickering;
unsigned char pfacing, pgotten, ppossee, pregotten;
unsigned char pfixct;
unsigned char psprid; 
signed int pvylast;
signed char pgtmx, pgtmy;
unsigned char pcharacter;

#ifdef PLAYER_SPINS
	unsigned char pspin;
#endif	

#ifdef PLAYER_GENITAL
	unsigned char pfacingh, pfacingv, pfacinglast;
#endif

#if defined (EVIL_TILE_MULTI) || defined (EVIL_TILE_CENTER) || defined (PLAYER_DIE_AND_RESPAWN)
	signed int pcx, pcy;
#endif

#ifdef PLAYER_SAFE
	unsigned char safe_prx, safe_pry;
	unsigned char safe_n_pant;
#endif

#ifdef SHOOTING_DRAINS
	unsigned char pgauge;
#endif

unsigned char pwashit;
unsigned char pstatespradder;

#ifdef PLAYER_HIDES
	unsigned char phidden;
#endif

#ifdef ENABLE_HOLES
	unsigned char pholed;
#endif

#ifdef ENABLE_SLIPPERY
	unsigned char pslips;
#endif

#ifdef ENABLE_WATER
	unsigned char pwater;
	unsigned char pwaterthrustct;
#endif

#ifdef PLAYER_PUSH_BOXES
	unsigned char pbx1, pby1;
#endif

#ifdef ENABLE_TILE_GET
	unsigned char ptile_get_ctr, optile_get_ctr;
#endif	

// ----------------------------------------------------------
// Enemies
// ----------------------------------------------------------
unsigned char _en_t, _en_x, _en_y;
unsigned char _en_x1, _en_x2, _en_y1, _en_y2;
signed char _en_mx, _en_my;
unsigned char _en_state, _en_ct;

#ifdef ENEMS_UPSIDE_DOWN
	unsigned char _en_ud;
#endif

#ifdef SPECCY
	unsigned char en_hl [N_ENEMS];
	unsigned char en_life [N_ENEMS];
	unsigned char en_s [N_ENEMS];
	unsigned char en_facing [N_ENEMS];
	unsigned char en_dying [N_ENEMS]; 
	unsigned char en_washit [N_ENEMS];

	#ifdef ENABLE_TYPE_7
		unsigned char en_fishing [N_ENEMS];
		unsigned char en_v [N_ENEMS];
	#endif

	#ifdef TYPE7_WITH_GENERATOR
		unsigned char en_gen_washit [N_ENEMS];
		unsigned char en_gen_dying [N_ENEMS];
		unsigned char en_gen_life [N_ENEMS];
	#endif

	#ifdef ENEMIES_NEED_FP
		#if defined (ENABLE_FANTY) || defined (ENABLE_ESPECTROS) || defined (ENABLE_PRECALC_TIMED_FANTY)
		unsigned char fanty_timer [N_ENEMS];
		signed int enf_x [N_ENEMS];
		signed char enf_vx [N_ENEMS];
		signed int _enf_x;
		signed char _enf_vx;
		#endif
		signed int enf_y [N_ENEMS];
		signed char enf_vy [N_ENEMS];
		signed int _enf_y;
		signed char _enf_vy;
	#endif

	unsigned char en_t [N_ENEMS];
	unsigned char en_x [N_ENEMS];
	unsigned char en_y [N_ENEMS];
	unsigned char en_x1 [N_ENEMS];
	unsigned char en_y1 [N_ENEMS];
	unsigned char en_x2 [N_ENEMS];
	unsigned char en_y2 [N_ENEMS];
	signed char en_mx [N_ENEMS];
	signed char en_my [N_ENEMS];

	unsigned char en_state [N_ENEMS];
	unsigned char en_ct [N_ENEMS];
#endif

#ifdef CPC
	extern unsigned char en_hl [N_ENEMS] @ (BASE_EN);
	extern unsigned char en_life [N_ENEMS] @ (BASE_EN + N_ENEMS);
	extern unsigned char en_s [N_ENEMS] @ (BASE_EN + 2*N_ENEMS);
	extern unsigned char en_facing [N_ENEMS] @ (BASE_EN + 3*N_ENEMS);
	extern unsigned char en_dying [N_ENEMS] @ (BASE_EN + 4*N_ENEMS);
	extern unsigned char en_washit [N_ENEMS] @ (BASE_EN + 5*N_ENEMS);
	extern unsigned char en_fishing [N_ENEMS] @ (BASE_EN + 6*N_ENEMS);
	extern unsigned char en_v [N_ENEMS] @ (BASE_EN + 7*N_ENEMS);
	extern unsigned char en_gen_washit [N_ENEMS] @ (BASE_EN + 8*N_ENEMS);
	extern unsigned char en_gen_dying [N_ENEMS] @ (BASE_EN + 9*N_ENEMS);
	extern unsigned char en_gen_life [N_ENEMS] @ (BASE_EN + 10*N_ENEMS);
	extern unsigned char *fanty_timer @ (BASE_EN + 11*N_ENEMS);
	extern signed int *enf_x @ (BASE_EN + 12*N_ENEMS);
	extern signed char *enf_vx @ (BASE_EN + 14*N_ENEMS);
	extern signed int _enf_x;
	extern signed char _enf_vx;
	extern signed int *enf_y @ (BASE_EN + 15*N_ENEMS);
	extern signed char *enf_vy @ (BASE_EN + 17*N_ENEMS);
	extern signed int _enf_y;
	extern signed char _enf_vy;
	extern unsigned char en_t [N_ENEMS] @ (BASE_EN + 18*N_ENEMS);
	extern unsigned char en_x [N_ENEMS] @ (BASE_EN + 19*N_ENEMS);
	extern unsigned char en_y [N_ENEMS] @ (BASE_EN + 20*N_ENEMS);
	extern unsigned char en_x1 [N_ENEMS] @ (BASE_EN + 21*N_ENEMS);
	extern unsigned char en_y1 [N_ENEMS] @ (BASE_EN + 22*N_ENEMS);
	extern unsigned char en_x2 [N_ENEMS] @ (BASE_EN + 23*N_ENEMS);
	extern unsigned char en_y2 [N_ENEMS] @ (BASE_EN + 24*N_ENEMS);
	extern signed char en_mx [N_ENEMS] @ (BASE_EN + 25*N_ENEMS);
	extern signed char en_my [N_ENEMS] @ (BASE_EN + 26*N_ENEMS);
	extern unsigned char en_state [N_ENEMS] @ (BASE_EN + 27*N_ENEMS);
	extern unsigned char en_ct [N_ENEMS] @ (BASE_EN + 28*N_ENEMS);
#endif

#ifdef PERSISTENT_ENEMIES

#ifdef SPECCY
	unsigned char ep_x [3*MAX_PANTS] @ BASE_EP;
	unsigned char ep_y [3*MAX_PANTS] @ (BASE_EP + 3*MAX_PANTS);
	signed char ep_mx [3*MAX_PANTS] @ (BASE_EP + 2*3*MAX_PANTS);
	signed char ep_my [3*MAX_PANTS] @ (BASE_EP + 3*3*MAX_PANTS);
	unsigned int ep_it;
#endif

#ifdef CPC
	unsigned char ep_x [3*MAX_PANTS] @ BASE_EP;
	unsigned char ep_y [3*MAX_PANTS] @ (BASE_EP + 3*MAX_PANTS);
	#ifdef PERSISTENT_ENEMIES_PACKED
		unsigned char ep_myx [3*MAX_PANTS] @ (BASE_EP + 2*3*MAX_PANTS);
	#else
		signed char ep_mx [3*MAX_PANTS] @ (BASE_EP + 2*3*MAX_PANTS);
		signed char ep_my [3*MAX_PANTS] @ (BASE_EP + 3*3*MAX_PANTS);
	#endif
	unsigned int ep_it;
#endif
	
#endif

#if defined(ENEMIES_CAN_DIE) && defined(PERSISTENT_DEATHS)	
	#ifdef SPECCY
		unsigned char ep_killed [MAX_PANTS * N_ENEMS];
	#endif
	#ifdef CPC
		unsigned char *ep_killed = BASE_EP + 4*3*MAX_PANTS;
	#endif
#endif

#ifdef ENEMS_UPSIDE_DOWN
	unsigned char en_ud [N_ENEMS];
#endif

unsigned char spr_id, en_fr;
unsigned char enoffs;
unsigned char genflipflop;
unsigned char is_platform;
unsigned char encelloffset;

#ifdef LINEAR_COLLIDES
	unsigned char en_collx, en_colly;
#endif

// ----------------------------------------------------------
// Hitter
// ----------------------------------------------------------
unsigned char hitter_hs_x;
unsigned char hitter_hs_y;
unsigned char hitter_x, hitter_y, hitter_frame;

// ----------------------------------------------------------
// Breakable walls
// ----------------------------------------------------------
#ifdef BREAKABLE_WALLS
	#ifdef SPECCY
		#if defined (MODE_128K)
			unsigned char brk_ac [BREAKABLE_MAX];
			unsigned char brk_slots [BREAKABLE_MAX];
			unsigned char brk_x [BREAKABLE_MAX];
			unsigned char  brk_y [BREAKABLE_MAX];
		unsigned char brk_slot;
	#else
			unsigned char brk_ac [BREAKABLE_MAX] @ BASE_BREAKABLE;
			unsigned char brk_slots [BREAKABLE_MAX] @ (BASE_BREAKABLE + BREAKABLE_MAX);
			unsigned char brk_x [BREAKABLE_MAX] @ (BASE_BREAKABLE + 2*BREAKABLE_MAX);
			unsigned char brk_y [BREAKABLE_MAX] @ (BASE_BREAKABLE + 3*BREAKABLE_MAX);
		unsigned char brk_slot;
	#endif
#ifdef BREAKABLE_TILE_SPECIAL
			#if defined (MODE_128K)
		unsigned char brk_sp [BREAKABLE_MAX];	
	#else	
				unsigned char brk_sp [BREAKABLE_MAX] @ (BASE_BREAKABLE + 4*BREAKABLE_MAX);
			#endif	
		#endif
	#endif
	#ifdef CPC
		// Stuff this in gaps in VRAM
		unsigned char brk_slot;
		unsigned char brk_ac [BREAKABLE_MAX] @ BASE_BREAKABLE;
		unsigned char brk_slots [BREAKABLE_MAX] @ (BASE_BREAKABLE + BREAKABLE_MAX);
		unsigned char brk_x [BREAKABLE_MAX] @ (BASE_BREAKABLE + 2*BREAKABLE_MAX);
		unsigned char brk_y [BREAKABLE_MAX] @ (BASE_BREAKABLE + 3*BREAKABLE_MAX);
		unsigned char brk_sp [BREAKABLE_MAX] @ (BASE_BREAKABLE + 4*BREAKABLE_MAX);
#endif
	unsigned char process_breakable;
#endif

// ----------------------------------------------------------
// Floating boxes
// ----------------------------------------------------------

#ifdef FLOATY_PUSH_BOXES
	#ifndef BREAKABLE_MAX
		#define BREAKABLE_MAX 0
	#endif
	#define BASE_FLOATY (BASE_BREAKABLE + 5*BREAKABLE_MAX)
	unsigned char fpb_slot;
	unsigned char fpb_ac [FPB_MAX] @ BASE_FLOATY;
	unsigned char fpb_slots [FPB_MAX] @ (BASE_FLOATY + FPB_MAX);
	unsigned char fpb_yx [FPB_MAX] @ (BASE_FLOATY + 2*FPB_MAX);
	unsigned char fpb_ct [FPB_MAX] @ (BASE_FLOATY + 3*FPB_MAX);

	unsigned char process_floaty;
#endif

// ----------------------------------------------------------
// Hotspots
// ----------------------------------------------------------
#ifndef DEACTIVATE_HOTSPOTS
	unsigned char hrx, hry, hrt;
	unsigned char max_hotspots_type_1;
	#ifdef HOTSPOTS_MAY_CHANGE
		unsigned char ht [MAX_PANTS];
	#endif
	#ifdef SPECCY
		unsigned char hact [MAX_PANTS];
	#endif
	#ifdef CPC
		unsigned char hact [MAX_PANTS] @ (BASE_EN + 29*N_ENEMS);
	#endif
#endif

// ----------------------------------------------------------
// Locks
// ----------------------------------------------------------
#ifdef HOTSPOT_TYPE_KEY
	unsigned char lkact [BOLTS_MAX];
#endif	

// ----------------------------------------------------------
// Cocos
// ----------------------------------------------------------
#ifdef ENABLE_COCOS
	signed int _coco_x, _coco_y;
	unsigned char coco_it;
	unsigned char coco_slot;
	#ifdef SPECCY
		signed int coco_x [COCOS_MAX], coco_y [COCOS_MAX];
		signed int coco_vx [COCOS_MAX], coco_vy [COCOS_MAX];
		unsigned char coco_slots [COCOS_MAX];
	#endif
	#ifdef CPC
		#define COCO_BASE (BASE_EN + 29*N_ENEMS) + MAX_PANTS
		signed int coco_x [COCOS_MAX]  @ COCO_BASE;
		signed int coco_y [COCOS_MAX]  @ COCO_BASE + 2*COCOS_MAX;
		signed int coco_vx [COCOS_MAX] @ COCO_BASE + 4*COCOS_MAX;
		signed int coco_vy [COCOS_MAX] @ COCO_BASE + 6*COCOS_MAX;
		unsigned char coco_slots [COCOS_MAX] @ COCO_BASE + 8*COCOS_MAX;
	#endif
#endif

// ----------------------------------------------------------
// ISR
// ----------------------------------------------------------
#ifdef SPECCY
unsigned char isrc;
#endif

#ifdef CPC
	extern unsigned char isrc [0];
	extern unsigned char arkc [0];
	#asm
		._isrc defb 0
		._arkc defb 0
	#endasm
#endif

// ----------------------------------------------------------
// Timed message
// ----------------------------------------------------------
unsigned char tm_ctr;

// ----------------------------------------------------------
// Scripting
// ----------------------------------------------------------
#ifdef SCRIPTING_ON
	unsigned char flags [MAX_FLAGS] @ 0xCFFF-MAX_FLAGS;
	unsigned char sc_n, sc_c;
	const unsigned char *next_script;
	const unsigned char *script;
	unsigned char script_result, sc_terminado, sc_continuar;
	unsigned char commands_executed;
	#ifdef ENABLE_FIRE_ZONE
		unsigned char fzx1, fzy1, fzx2, fzy2, f_zone_ac;
	#endif
	unsigned char *scripts_index;
	#ifdef ACTION_KEY_DOWN
		unsigned char down_debounce;
	#endif
#endif
