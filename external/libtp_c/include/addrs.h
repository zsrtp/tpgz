#ifndef LIB_TP_ADDRS
#define LIB_TP_ADDRS

#ifndef REL_MODULE
#ifdef GCN_NTSCU
// System
#define tp_memset_addr 0x8026f95c
#define tp_memalign_addr 0x80263228
#define tp_free_addr 0x80263260
#define tp_osReport_addr 0x80006ABC
#define tp_memcpy_addr 0x80003540
#define tp_getLayerNo_addr 0x8002B434
#define tp_getSave_addr 0x800350bc
#define tp_putSave_addr 0x800350f0
#define tp_sprintf_addr 0x803664dc
#define tp_vsnprintf_addr 0x80366690
#define tp_strcpy_addr 0x80368b2c
#define tp_strlen_addr 0x80368be4
#define tp_strcmp_addr 0x80368994
#ifdef PR_TEST
#define tp_myExceptionCallback_addr 0x8000b7c8
#endif

// Math
#define tp_atan_addr 0x8036bca4
#define tp_ceil_addr 0x8036bebc
#define tp_copysign_addr 0x8036c000
#define tp_cos_addr 0x8036c028
#define tp_floor_addr 0x8036c0fc
#define tp_frexp_addr 0x8036c244
#define tp_ldexp_addr 0x8036c2d0
#define tp_modf_addr 0x8036c494
#define tp_sin_addr 0x8036c590
#define tp_tan_addr 0x8036c668
#define tp_acos_addr 0x8036c6e0
#define tp_asin_addr 0x8036c700
#define tp_atan2_addr 0x8036c720
#define tp_exp_addr 0x8036c740
#define tp_fmod_addr 0x8036c760
#define tp_pow_addr 0x8036c780
#define tp_fastSqrt_addr 0x80182a24
#define tp_sqrt_addr 0x8036ca54
#define tp_sincosTable_addr 0x80439A20

// Lib
#define cLib_chaseF_addr 0x80270740
#define cLib_targetAngleY_addr 0x80270c04
#define cLib_addCalc_addr 0x8026f97c

// Controller
#define tp_mPadStatus_addr 0x804343F0
#define tp_mPadButton_addr 0x80434420
#define tp_mPadMStick_addr 0x804344E0
#define tp_mPadSStick_addr 0x80434520
#define tp_JUTGamePadRead_addr 0x802e08e4
#define tp_cPadInfo_addr 0x803DD2E8

// TP
#define tp_globalCounters_addr 0x80430CD8
#define tp_zelAudio_addr 0x803DBF4C
#define tp_gameInfo_addr 0x804061C0
#define tp_sConsole_addr 0x80450C90
#define tp_fopScnRq_addr 0x80450CE0
#define tp_titleScreenPtr_addr 0x803A3A38
#define tp_matrixPtr_addr 0x803F1E10
#define tp_rng_addr 0x80451168

// Items
#define tp_clawshot_addr 0x8038E9C0
#define tp_clawshot_checkbg_addr 0x801087b0
#define tp_ironboots_addr 0x8038E7F4
#define tp_spinner_addr 0x8038EA30
#define tp_ball_and_chain_addr 0x8038EA70
#define tp_bottle_addr 0x8038E90C

// Actor
#define tp_actor_addr 0x80450610
#define tp_actor_stopstatus_addr 0x80450CBC

// Draw
#define tp_draw_addr 0x8042EBC8

// Link
#define tp_link_human_frontroll_addr 0x8038D7BC
#define tp_link_human_sidestep_addr 0x8038D864
#define tp_link_human_backjump_addr 0x8038D82C
#define tp_link_human_slide_addr 0x8038D8CC
#define tp_link_human_swim_addr 0x8038ED2C
#define tp_link_wolf_general_addr 0x8038EE28
#define tp_link_wolf_swim_addr 0x8038f8b4

// Inventory
#define tp_execItemGet_addr 0x80097E8C

// Scene
#define tp_setTimePass_addr 0x80024DB0

// GX
#define GXSetBlendMode_addr 0x8035FBF0
#define GXBegin_addr 0x8035C764
#define GXSetVtxAttrFmt_addr 0x8035B5C4
#define GXLoadPosMtxImm_addr 0x8036024C
#define GXSetNumIndStages_addr 0x8035F0D4
#define GXSetTevDirect_addr 0x8035F0F8
#define GXSetAlphaCompare_addr 0x8035F624
#define GXSetZMode_addr 0x8035FC9C
#define GXSetTevOp_addr 0x8035F198
#define GXSetNumChans_addr 0x8035DB30
#define GXSetNumTevStages_addr 0x8035F890
#define GXSetNumTexGens_addr 0x8035BDFC
#define GXSetTevOrder_addr 0x8035F6F4
#define GXSetTevColorIn_addr 0x8035F224
#define GXSetTevAlphaIn_addr 0x8035F268
#define GXSetTevColorOp_addr 0x8035F2AC
#define GXSetTevAlphaOp_addr 0x8035F314
#define GXSetCullMode_addr 0x8035C984
#define GXLoadTexMtxImm_addr 0x80360320
#define GXSetChanCtrl_addr 0x8035DB6C
#define GXSetCurrentMtx_addr 0x803602EC
#define GXSetTexCoordGen2_addr 0x8035BB7C
#define GXSetLineWidth_addr 0x8035C8BC
#define GXClearVtxDesc_addr 0x8035B58C
#define GXSetVtxDesc_addr 0x8035AEB8
#define GXFlush_addr 0x8035becc
#define GXInitTexObj_addr 0x8035DE40
#define GXLoadTexObj_addr 0x8035E414
#define GXInvalidateTexAll_addr 0x8035E664
#define GXSetProjection_addr 0x803600D4
#define GXSetScissor_addr 0x803604D0
#define GXGetScissor_addr 0x80360548
#define wgPipe_addr 0xCC008000

// misc functions (sort later)
#define tp_cDyl_InitAsync_addr 0x80018764
#define tp_fapGm_Execute_addr 0x80018a6c
#define tp_draw_console_addr 0x802e8384
#define tp_PADRead_addr 0x8034eea0
#define tp_setSpecialGravity_addr 0x800bb770
#define tp_checkCastleTownUseItem_addr 0x800c0678
#define tp_query042_addr 0x8024bfec
#define tp_cc_at_check_addr 0x80087c04

// d_bg_s
#define cBgS__GroundCross_addr 0x800744a0

// d_save
#define dSv_player_item_c__setItem_addr 0x80032fb8
#define dSv_player_item_c__getItem_addr 0x80033030
#define dSv_player_item_record_c__setBombNum_addr 0x80033f6c
#define dSv_player_item_record_c__getBombNum_addr 0x80033f7c
#define dSv_player_status_a_c__getSelectItemIndex_addr 0x80032a5c
#define dSv_player_status_b_c__isTransformLV_addr 0x80032bec
#define dSv_player_status_b_c__onTransformLV_addr 0x80032bd0
#define dSv_light_drop_c__setLightDropNum_addr 0x80034320
#define dSv_light_drop_c__getLightDropNum_addr 0x80034340
#define dSv_info_c__onSwitch_addr 0x80035200
#define dSv_info_c__offSwitch_addr 0x800352b0
#define dSv_memBit_c__isSwitch_addr 0x80034860
#define dSv_memBit_c__onSwitch_addr 0x80034810
#define dSv_memBit_c__offSwitch_addr 0x80034838
#define dSv_memBit_c__isDungeonItem_addr 0x80034934
#define dSv_memBit_c__onDungeonItem_addr 0x80034918
#define dSv_player_get_item_c__onFirstBit_addr 0x80033e60
#define dSv_player_get_item_c__offFirstBit_addr 0x80033e94
#define dSv_event_c__isEventBit_addr 0x800349bc
#define dSv_event_c__offEventBit_addr 0x800349a4
#define dSv_event_c__onEventBit_addr 0x8003498c
#define dSv_player_return_place_c__set_addr 0x80032d1c

// d_meter2_info
#define g_meter2_info_addr 0x80430188

// d_com_inf_game
#define dComIfGs_setSelectItemIndex_addr 0x8002dcc4
#define dComIfGs_getMixItemIndex_addr 0x8002ddc8
#define dComIfGs_setMixItemIndex_addr 0x8002dd08
#define dComIfGp_getEvent_addr 0x801412f8
#define dComIfGp_getEventManager_addr 0x8014134c
#define dComIfGs_isItemFirstBit_addr 0x80141264
#define dComIfGs_getRupee_addr 0x80141990
#define dComIfGs_onZoneSwitch_addr 0x8002d94c
#define dComIfGs_onOneZoneSwitch_addr 0x8002da9c

// d_stage
#define dStage_nextStage_c__set_addr 0x80023e28

// d_menu_window
#define dMw_c__offMenuRing_addr 0x801fa0f0
#define dMw_c__key_wait_init_addr 0x801fa13c
#define dMw_c__ring_close_proc_addr 0x801fb064
#define dMw_c__ring_open_proc_addr 0x801fafdc
#define dMw_c__collect_close_proc_addr 801fb1a0
#define dMw_c__ring_delete_addr 0x801fbf60
#define dMw_c__isEventCheck_addr 0x801fcf84
#define dMw_c__execute_addr 0x801fd2d8
#define dMw_c___delete_addr 0x801fd67c
#define dMw_c__fmap_close_proc_addr 0x801fb36c
#define dMw_c__dmap_close_proc_addr 0x801fb5dc
#define dMw_c__collect_save_close_proc_addr 0x801fb6d8
#define dMw_c__collect_option_close_proc_addr 0x801fb800
#define dMw_c__collect_letter_close_proc_addr 0x801fb900
#define dMw_c__collect_fishing_close_proc_addr 0x801fba00
#define dMw_c__collect_skill_close_proc_addr 0x801fbb00
#define dMw_c__collect_insect_close_proc_addr 0x801fbc00
#define dMw_c__insect_close_proc_addr 0x801fbd64

// m_Do_audio
#define mDoAud_seStartLevel_addr 0x8014113c

// JKernel
#define JKernel__operator_new_addr 0x802cec4c
#define JKernel__operator_delete_addr 0x802ced3c
#define JKRArchive__getResource2_addr 0x802d5c64
#define tp_zeldaHeap_addr 0x80450c2c
#define tp_gameHeap_addr 0x80450c28
#define tp_archiveHeap_addr 0x80450c34
#define JKRExpHeap__getUsedSize_addr 0x802cfce8
#define JKRHeap__getFreeSize_addr 0x802ce72c
#define JKRHeap__getTotalFreeSize_addr 0x802ce784
#define JKRExpHeap__do_getTotalFreeSize_addr 0x802cfc84
#define JKRHeap__alloc_addr 0x802ce474

// J3DSys
#define j3dSys_addr 0x80434ac8

// J3DPacket
#define J3DDrawBuffer__entryImm_addr 0x8032548c
#define J3DPacket__entry_addr 0x80312750

// J2DPicture
#define J2DPicture__J2DPicture4_addr 0x802fc708
#define J2DPicture__draw_addr 0x802fdc70

// J2DPane
#define J2DPane__J2DPane1_addr 0x802f5bf8

// J2DTextBox
#define J2DTextBox__J2DTextBox1_addr 0x802ff660
#define J2DTextBox__setFont_addr 0x80300278
#define J2DTextBox__setString_addr 0x80300660
#define J2DTextBox__draw2_addr 0x80300490

// d_a_alink
#define daAlink_c__checkStageName_addr 0x8009da60
#define daAlink_c__posMove_addr 0x800bbf68

// f_op_actor_mng
#define fopAcM_create_addr 0x80019D98
#define fopAcM_gc_c__gndCheck_addr 0x8001dcbc
#define g_fopAcTg_Queue_addr 0x803A35E0
#define fopAcM_gc_c__mGroundY_addr 0x80450cd0


// f_op_actor_iter
#define fopAcIt_Judge_addr 0x800197f8

// f_op_msg_mng
#define fopMsgM_SearchByID_addr 0x8001fa24

// f_pc_searcher
#define fpcSch_JudgeForPName_addr 0x80023578

// d_kankyo
#define g_env_light_addr 0x8042ca54

// d_s_play
#define sPauseTimer_addr 0x80451125

// d_cc_s
#define dCcS__draw_addr 0x800872d0

// m_Do_graphic
#define dScnPly_BeforeOfPaint_addr 0x80008424

// m_Do_ext
#define mDoExt_getMesgFont_addr 0x800149f0

// m_Do_controller_pad
#define mDoCPd_c__m_gamePad_addr 0x803DD2D8

// m_Do_mtx
#define mDoMtx_stack_c__now_addr 0x803dd470
#define mDoMtx_XYZrotM__addr 0x8000c164
#define mDoMtx_stack_c__scaleM_addr 0x8000ce38

#endif

#ifdef GCN_PAL
// System
#define tp_memset_addr 0x8027075c
#define tp_memalign_addr 0x80264028
#define tp_free_addr 0x80264060
#define tp_osReport_addr 0x80006ABC
#define tp_memcpy_addr 0x80003540
#define tp_getLayerNo_addr 0x8002b4dc
#define tp_getSave_addr 0x800351ec
#define tp_putSave_addr 0x80035220
#define tp_sprintf_addr 0x8036730c
#define tp_strcpy_addr 0x8036995c
#define tp_strlen_addr 0x80369a14
#define tp_strcmp_addr 0x803697c4

// Math
#define tp_atan_addr 0x8036cad4
#define tp_ceil_addr 0x8036ccec
#define tp_copysign_addr 0x8036ce30
#define tp_cos_addr 0x8036ce58
#define tp_floor_addr 0x8036cf2c
#define tp_frexp_addr 0x8036d074
#define tp_ldexp_addr 0x8036d100
#define tp_modf_addr 0x8036d2c4
#define tp_sin_addr 0x8036d3c0
#define tp_tan_addr 0x8036d498
#define tp_acos_addr 0x8036d510
#define tp_asin_addr 0x8036d530
#define tp_atan2_addr 0x8036d550
#define tp_exp_addr 0x8036d570
#define tp_fmod_addr 0x8036d590
#define tp_pow_addr 0x8036d5b0
#define tp_fastSqrt_addr 0x80182c30
#define tp_sqrt_addr 0x8036d884
#define tp_sincosTable_addr 0x8043b9e0

// Lib
#define cLib_chaseF_addr 0x80271540
#define cLib_targetAngleY_addr 0x80271a04
#define cLib_addCalc_addr 0x8027077c

// Controller
#define tp_mPadStatus_addr 0x804363b0
#define tp_mPadButton_addr 0x804363e0
#define tp_mPadMStick_addr 0x804364a0
#define tp_mPadSStick_addr 0x804364e0
#define tp_JUTGamePadRead_addr 0x802e16e4
#define tp_cPadInfo_addr 0x803df288

// TP
#define tp_globalCounters_addr 0x80432c98
#define tp_zelAudio_addr 0x803ddeec
#define tp_gameInfo_addr 0x80408160
#define tp_sConsole_addr 0x80452c50
#define tp_fopScnRq_addr 0x80452ca0
#define tp_titleScreenPtr_addr 0x803a5718
#define tp_matrixPtr_addr 0x803f3db0
#define tp_rng_addr 0x80453130

// Items
#define tp_clawshot_addr 0x803901c0
#define tp_clawshot_checkbg_addr 0x801089bc
#define tp_ironboots_addr 0x8038fff4
#define tp_spinner_addr 0x80390230
#define tp_ball_and_chain_addr 0x80390270
#define tp_bottle_addr 0x8039010c

// Actor
#define tp_actor_addr 0x804525d0
#define tp_actor_stopstatus_addr 0x80452c7c

// Draw
#define tp_draw_addr 0x80430b88

// Link
#define tp_link_human_frontroll_addr 0x8038efbc
#define tp_link_human_sidestep_addr 0x8038f064
#define tp_link_human_backjump_addr 0x8038f02c
#define tp_link_human_slide_addr 0x8038f0cc
#define tp_link_human_swim_addr 0x8039052c
#define tp_link_wolf_general_addr 0x80390628
#define tp_link_wolf_swim_addr 0x803910b4

// Inventory
#define tp_execItemGet_addr 0x80097fbc

// Scene
#define tp_setTimePass_addr 0x80024e58

// GX
#define GXSetBlendMode_addr 0x80360a20
#define GXBegin_addr 0x8035d594
#define GXSetVtxAttrFmt_addr 0x8035c3f4
#define GXLoadPosMtxImm_addr 0x8036107c
#define GXSetNumIndStages_addr 0x8035ff04
#define GXSetTevDirect_addr 0x8035ff28
#define GXSetAlphaCompare_addr 0x80360454
#define GXSetZMode_addr 0x80360acc
#define GXSetTevOp_addr 0x8035ffc8
#define GXSetNumChans_addr 0x8035e960
#define GXSetNumTevStages_addr 0x803606c0
#define GXSetNumTexGens_addr 0x8035cc2c
#define GXSetTevOrder_addr 0x80360524
#define GXSetTevColorIn_addr 0x80360054
#define GXSetTevAlphaIn_addr 0x80360098
#define GXSetTevColorOp_addr 0x803600dc
#define GXSetTevAlphaOp_addr 0x80360144
#define GXSetCullMode_addr 0x8035d7b4
#define GXLoadTexMtxImm_addr 0x80361150
#define GXSetChanCtrl_addr 0x8035e99c
#define GXSetCurrentMtx_addr 0x8036111c
#define GXSetTexCoordGen2_addr 0x8035c9ac
#define GXSetLineWidth_addr 0x8035d6ec
#define GXClearVtxDesc_addr 0x8035c3bc
#define GXSetVtxDesc_addr 0x8035bce8
#define GXFlush_addr 0x8035ccfc
#define GXInitTexObj_addr 0x8035ec70
#define GXLoadTexObj_addr 0x8035f244
#define GXInvalidateTexAll_addr 0x8035f494
#define GXSetProjection_addr 0x80360f04
#define GXSetScissor_addr 0x80361300
#define GXGetScissor_addr 0x80361378
#define wgPipe_addr 0xCC008000

// function hooks (move to correct categories later)
#define tp_cDyl_InitAsync_addr 0x8001880c
#define tp_fapGm_Execute_addr 0x80018b14
#define tp_draw_console_addr 0x802e9184
#define tp_PADRead_addr 0x8034fcd0
#define tp_setSpecialGravity_addr 0x800bb97c
#define tp_checkCastleTownUseItem_addr 0x800c0884
#define tp_query042_addr 0x8024c690
#define tp_cc_at_check_addr 0x80087d34

// d_bg_s
#define cBgS__GroundCross_addr 0x800745d0

// d_save
#define dSv_player_item_c__setItem_addr 0x80033060
#define dSv_player_item_c__getItem_addr 0x800330d8
#define dSv_player_item_record_c__setBombNum_addr 0x80034014
#define dSv_player_item_record_c__getBombNum_addr 0x80034024
#define dSv_player_status_a_c__getSelectItemIndex_addr 0x80032b04
#define dSv_player_status_b_c__isTransformLV_addr 0x80032c94
#define dSv_player_status_b_c__onTransformLV_addr 0x80032c78
#define dSv_light_drop_c__setLightDropNum_addr 0x800343c8
#define dSv_light_drop_c__getLightDropNum_addr 0x800343e8
#define dSv_info_c__onSwitch_addr 0x80035330
#define dSv_info_c__offSwitch_addr 0x800353e0
#define dSv_memBit_c__isSwitch_addr 0x80035490
#define dSv_memBit_c__onSwitch_addr 0x80034940
#define dSv_memBit_c__offSwitch_addr 0x80034968
#define dSv_memBit_c__isDungeonItem_addr 0x80034a64
#define dSv_memBit_c__onDungeonItem_addr 0x80034a48
#define dSv_player_get_item_c__onFirstBit_addr 0x80033f08
#define dSv_player_get_item_c__offFirstBit_addr 0x80033f3c
#define dSv_event_c__isEventBit_addr 0x80034aec
#define dSv_event_c__offEventBit_addr 0x80034ad4
#define dSv_event_c__onEventBit_addr 0x80034abc
#define dSv_player_return_place_c__set_addr 0x80032dc4

// d_meter2_info
#define g_meter2_info_addr 0x80432148

// d_com_inf_game
#define dComIfGs_setSelectItemIndex_addr 0x8002dd6c
#define dComIfGs_getMixItemIndex_addr 0x8002de70
#define dComIfGs_setMixItemIndex_addr 0x8002ddb0
#define dComIfGp_getEvent_addr 0x80141504
#define dComIfGp_getEventManager_addr 0x80141558
#define dComIfGs_isItemFirstBit_addr 0x80141470
#define dComIfGs_getRupee_addr 0x80141b9c
#define dComIfGs_onZoneSwitch_addr 0x8002d9f4
#define dComIfGs_onOneZoneSwitch_addr 0x8002db44

// d_stage
#define dStage_nextStage_c__set_addr 0x80023ed0

// d_menu_window
#define dMw_c__offMenuRing_addr 0x801fa3b4
#define dMw_c__key_wait_init_addr 0x801fa400
#define dMw_c__ring_close_proc_addr 0x801fb328
#define dMw_c__ring_open_proc_addr 0x801fb2a0
#define dMw_c__collect_close_proc_addr 0x801fb464
#define dMw_c__ring_delete_addr 0x801fc224
#define dMw_c__isEventCheck_addr 0x801fd248
#define dMw_c__execute_addr 0x801fd59c
#define dMw_c___delete_addr 0x801fd940
#define dMw_c__fmap_close_proc_addr 0x801fb630
#define dMw_c__dmap_close_proc_addr 0x801fb8a0
#define dMw_c__collect_save_close_proc_addr 0x801fb99c
#define dMw_c__collect_option_close_proc_addr 0x801fbac4
#define dMw_c__collect_letter_close_proc_addr 0x801fbbc4
#define dMw_c__collect_fishing_close_proc_addr 0x801fbcc4
#define dMw_c__collect_skill_close_proc_addr 0x801fbdc4
#define dMw_c__collect_insect_close_proc_addr 0x801fbec4
#define dMw_c__insect_close_proc_addr 0x801fc028


// m_Do_audio
#define mDoAud_seStartLevel_addr 0x80141348

// JKernel
#define JKernel__operator_new_addr 0x802cfa4c
#define JKernel__operator_delete_addr 0x802cfb3c
#define JKRArchive__getResource2_addr 0x802d6a64
#define tp_zeldaHeap_addr 0x80452bec
#define tp_gameHeap_addr 0x80452be8
#define tp_archiveHeap_addr 0x80452bf4
#define JKRExpHeap__getUsedSize_addr 0x802d0ae8
#define JKRHeap__getFreeSize_addr 0x802cf52c
#define JKRHeap__getTotalFreeSize_addr 0x802cf584
#define JKRExpHeap__do_getTotalFreeSize_addr 0x802d0a84
#define JKRHeap__alloc_addr 0x802cf274

// J3DSys
#define j3dSys_addr 0x80436a88

// J3DPacket
#define J3DDrawBuffer__entryImm_addr 0x8032628c
#define J3DPacket__entry_addr 0x80313550

// J2DPicture
#define J2DPicture__J2DPicture4_addr 0x802fd508
#define J2DPicture__draw_addr 0x802fea70

// J2DPane
#define J2DPane__J2DPane1_addr 0x802f69f8

// J2DTextBox
#define J2DTextBox__J2DTextBox1_addr 0x80300460
#define J2DTextBox__setFont_addr 0x80301078
#define J2DTextBox__setString_addr 0x80301460
#define J2DTextBox__draw2_addr 0x80301290

// d_a_alink
#define daAlink_c__checkStageName_addr 0x8009dc6c
#define daAlink_c__posMove_addr 0x800bc174

// f_op_actor_mng
#define fopAcM_create_addr 0x80019e40
#define fopAcM_gc_c__gndCheck_addr 0x8001dd64
#define g_fopAcTg_Queue_addr 0x803a52c0
#define fopAcM_gc_c__mGroundY_addr 0x80452c90

// f_op_actor_iter
#define fopAcIt_Judge_addr 0x800198a0

// f_op_msg_mng
#define fopMsgM_SearchByID_addr 0x8001facc

// f_pc_searcher
#define fpcSch_JudgeForPName_addr 0x80023620

// d_kankyo
#define g_env_light_addr 0x8042ea14

// d_s_play
#define sPauseTimer_addr 0x804530ED

// m_Do_ext
#define mDoExt_getMesgFont_addr 0x800149a4

// m_Do_controller_pad
#define mDoCPd_c__m_gamePad_addr 0x803df278

// m_Do_mtx
#define mDoMtx_stack_c__now_addr 0x803df410
#define mDoMtx_XYZrotM__addr 0x8000c118
#define mDoMtx_stack_c__scaleM_addr 0x8000cdec

#endif

#ifdef GCN_NTSCJ
// System
#define tp_memset_addr 0x80271d8c
#define tp_memalign_addr 0x80265658
#define tp_free_addr 0x80265690
#define tp_osReport_addr 0x80006ABC
#define tp_memcpy_addr 0x80003540
#define tp_getLayerNo_addr 0x8002c97c
#define tp_getSave_addr 0x800350bc
#define tp_putSave_addr 0x800350f0
#define tp_sprintf_addr 0x80368978
#define tp_strcpy_addr 0x8036afc8
#define tp_strlen_addr 0x8036b080
#define tp_strcmp_addr 0x8036ae30

// Math
#define tp_atan_addr 0x8036e140
#define tp_ceil_addr 0x8036e358
#define tp_copysign_addr 0x8036e49c
#define tp_cos_addr 0x8036e4c4
#define tp_floor_addr 0x8036e598
#define tp_frexp_addr 0x8036e6e0
#define tp_ldexp_addr 0x8036e76c
#define tp_modf_addr 0x8036e930
#define tp_sin_addr 0x8036ea2c
#define tp_tan_addr 0x8036eb04
#define tp_acos_addr 0x8036eb7c
#define tp_asin_addr 0x8036eb9c
#define tp_atan2_addr 0x8036ebbc
#define tp_exp_addr 0x8036ebdc
#define tp_fmod_addr 0x8036ebfc
#define tp_pow_addr 0x8036ec1c
#define tp_fastSqrt_addr 0x80182a70
#define tp_sqrt_addr 0x8036eef0
#define tp_sincosTable_addr 0x80433b60

// Lib
#define cLib_chaseF_addr 0x80272b70
#define cLib_targetAngleY_addr 0x80273034
#define cLib_addCalc_addr 0x80271dac

// Controller
#define tp_mPadStatus_addr 0x8042e530
#define tp_mPadButton_addr 0x8042e560
#define tp_mPadMStick_addr 0x8042e620
#define tp_mPadSStick_addr 0x8042e660
#define tp_JUTGamePadRead_addr 0x802e2d80
#define tp_cPadInfo_addr 0x803d7428

// TP
#define tp_globalCounters_addr 0x8042ae18
#define tp_zelAudio_addr 0x803d608c
#define tp_gameInfo_addr 0x80400300
#define tp_sConsole_addr 0x8044add0
#define tp_fopScnRq_addr 0x8044ae20
#define tp_titleScreenPtr_addr 0x8039db98
#define tp_matrixPtr_addr 0x803ebf50
#define tp_rng_addr 0x8044b2a8

// Items
#define tp_clawshot_addr 0x80388a40
#define tp_clawshot_checkbg_addr 0x801087e8
#define tp_ironboots_addr 0x80388874
#define tp_spinner_addr 0x80388ab0
#define tp_ball_and_chain_addr 0x80388af0
#define tp_bottle_addr 0x8038898c

// Actor
#define tp_actor_addr 0x8044a750
#define tp_actor_stopstatus_addr 0x8044adfc

// Draw
#define tp_draw_addr 0x80428d08

// Link
#define tp_link_human_frontroll_addr 0x8038783c
#define tp_link_human_sidestep_addr 0x803878e4
#define tp_link_human_backjump_addr 0x803878ac
#define tp_link_human_slide_addr 0x8038794c
#define tp_link_human_swim_addr 0x80388dac
#define tp_link_wolf_general_addr 0x80388ea8
#define tp_link_wolf_swim_addr 0x80389934

// Inventory
#define tp_execItemGet_addr 0x80097ecc

// Scene
#define tp_setTimePass_addr 0x80024db0

// GX
#define GXSetBlendMode_addr 0x8036208c
#define GXBegin_addr 0x8035ec00
#define GXSetVtxAttrFmt_addr 0x8035da60
#define GXLoadPosMtxImm_addr 0x803626e8
#define GXSetNumIndStages_addr 0x80361570
#define GXSetTevDirect_addr 0x80361594
#define GXSetAlphaCompare_addr 0x80361ac0
#define GXSetZMode_addr 0x80362138
#define GXSetTevOp_addr 0x80361634
#define GXSetNumChans_addr 0x8035ffcc
#define GXSetNumTevStages_addr 0x80361d2c
#define GXSetNumTexGens_addr 0x8035e298
#define GXSetTevOrder_addr 0x80361b90
#define GXSetTevColorIn_addr 0x803616c0
#define GXSetTevAlphaIn_addr 0x80361704
#define GXSetTevColorOp_addr 0x80361748
#define GXSetTevAlphaOp_addr 0x803617b0
#define GXSetCullMode_addr 0x8035ee20
#define GXLoadTexMtxImm_addr 0x803627bc
#define GXSetChanCtrl_addr 0x80360008
#define GXSetCurrentMtx_addr 0x80362788
#define GXSetTexCoordGen2_addr 0x8035e018
#define GXSetLineWidth_addr 0x8035ed58
#define GXClearVtxDesc_addr 0x8035da28
#define GXSetVtxDesc_addr 0x8035d354
#define GXFlush_addr 0x8035e368
#define GXInitTexObj_addr 0x803602dc
#define GXLoadTexObj_addr 0x803608b0
#define GXInvalidateTexAll_addr 0x80360b00
#define GXSetProjection_addr 0x80362570
#define GXSetScissor_addr 0x8036296c
#define GXGetScissor_addr 0x803629e4
#define wgPipe_addr 0xCC008000

// function hooks (move to correct categories later)
#define tp_cDyl_InitAsync_addr 0x80018764
#define tp_fapGm_Execute_addr 0x80018a6c
#define tp_draw_console_addr 0x802ea820
#define tp_PADRead_addr 0x8035133c
#define tp_setSpecialGravity_addr 0x800bb7a8
#define tp_checkCastleTownUseItem_addr 0x800c06b0
#define tp_query042_addr 0x8024d954
#define tp_cc_at_check_addr 0x80087c44

// d_bg_s
#define cBgS__GroundCross_addr 0x800744e0

// d_save
#define dSv_player_item_c__setItem_addr 0x80032fb8
#define dSv_player_item_c__getItem_addr 0x80033030
#define dSv_player_item_record_c__setBombNum_addr 0x80033f6c
#define dSv_player_item_record_c__getBombNum_addr 0x80033f7c
#define dSv_player_status_a_c__getSelectItemIndex_addr 0x80032a5c
#define dSv_player_status_b_c__isTransformLV_addr 0x80032bec
#define dSv_player_status_b_c__onTransformLV_addr 0x80032bd0
#define dSv_light_drop_c__setLightDropNum_addr 0x80034320
#define dSv_light_drop_c__getLightDropNum_addr 0x80034340
#define dSv_info_c__onSwitch_addr 0x80035200
#define dSv_info_c__offSwitch_addr 0x800352b0
#define dSv_memBit_c__isSwitch_addr 0x80035360
#define dSv_memBit_c__onSwitch_addr 0x80034810
#define dSv_memBit_c__offSwitch_addr 0x80034838
#define dSv_memBit_c__isDungeonItem_addr 0x80034934
#define dSv_memBit_c__onDungeonItem_addr 0x80034918
#define dSv_player_get_item_c__onFirstBit_addr 0x80033e60
#define dSv_player_get_item_c__offFirstBit_addr 0x80033e94
#define dSv_event_c__isEventBit_addr 0x800349bc
#define dSv_event_c__offEventBit_addr 0x800349a4
#define dSv_event_c__onEventBit_addr 0x8003498c
#define dSv_player_return_place_c__set_addr 0x80032d1c

// d_meter2_info
#define g_meter2_info_addr 0x8042a2c8

// d_com_inf_game
#define dComIfGs_setSelectItemIndex_addr 0x8002dcc4
#define dComIfGs_getMixItemIndex_addr 0x8002ddc8
#define dComIfGs_setMixItemIndex_addr 0x8002dd08
#define dComIfGp_getEvent_addr 0x80141344
#define dComIfGp_getEventManager_addr 0x80141398
#define dComIfGs_isItemFirstBit_addr 0x801412b0
#define dComIfGs_getRupee_addr 0x801419dc
#define dComIfGs_onZoneSwitch_addr 0x8002d94c
#define dComIfGs_onOneZoneSwitch_addr 0x8002da9c

// d_stage
#define dStage_nextStage_c__set_addr 0x80023e28

// d_menu_window
#define dMw_c__offMenuRing_addr 0x801fa7e8
#define dMw_c__key_wait_init_addr 0x801fa834
#define dMw_c__ring_close_proc_addr 0x801fb75c
#define dMw_c__ring_open_proc_addr 0x801fb6d4
#define dMw_c__collect_close_proc_addr 0x801fb898
#define dMw_c__ring_delete_addr 0x801fc658
#define dMw_c__isEventCheck_addr 0x801fd67c
#define dMw_c__execute_addr 0x801fd9d0
#define dMw_c___delete_addr 0x801fdd74
#define dMw_c__fmap_close_proc_addr 0x801fba64
#define dMw_c__dmap_close_proc_addr 0x801fbcd4
#define dMw_c__collect_save_close_proc_addr 0x801fbdd0
#define dMw_c__collect_option_close_proc_addr 0x801fbef8
#define dMw_c__collect_letter_close_proc_addr 0x801fbff8
#define dMw_c__collect_fishing_close_proc_addr 0x801fc0f8
#define dMw_c__collect_skill_close_proc_addr 0x801fc1f8
#define dMw_c__collect_insect_close_proc_addr 0x801fc2f8
#define dMw_c__insect_close_proc_addr 0x801fc45c

// m_Do_audio
#define mDoAud_seStartLevel_addr 0x80141188

// JKernel
#define JKernel__operator_new_addr 0x802d10e8
#define JKernel__operator_delete_addr 0x802d11d8
#define JKRArchive__getResource2_addr 0x802d8100
#define tp_zeldaHeap_addr 0x8044ad6c
#define tp_gameHeap_addr 0x8044ad68
#define tp_archiveHeap_addr 0x8044ad74
#define JKRExpHeap__getUsedSize_addr 0x802d2184
#define JKRHeap__getFreeSize_addr 0x802d0bc8
#define JKRHeap__getTotalFreeSize_addr 0x802d0c20
#define JKRExpHeap__do_getTotalFreeSize_addr 0x802d2120
#define JKRHeap__alloc_addr 0x802d0910

// J3DSys
#define j3dSys_addr 0x8042ec08

// J3DPacket
#define J3DDrawBuffer__entryImm_addr 0x80327928
#define J3DPacket__entry_addr 0x80314bec

// J2DPicture
#define J2DPicture__J2DPicture4_addr 0x802feba4
#define J2DPicture__draw_addr 0x8030010c

// J2DPane
#define J2DPane__J2DPane1_addr 0x802f8094

// J2DTextBox
#define J2DTextBox__J2DTextBox1_addr 0x80301afc
#define J2DTextBox__setFont_addr 0x80302714
#define J2DTextBox__setString_addr 0x80302afc
#define J2DTextBox__draw2_addr 0x8030292c

// d_a_alink
#define daAlink_c__checkStageName_addr 0x8009da98
#define daAlink_c__posMove_addr 0x800bbfa0

// f_op_actor_mng
#define fopAcM_create_addr 0x80019d98
#define fopAcM_gc_c__gndCheck_addr 0x8001dcbc
#define g_fopAcTg_Queue_addr 0x8039d740
#define fopAcM_gc_c__mGroundY_addr 0x8044ae10

// f_op_actor_iter
#define fopAcIt_Judge_addr 0x800197f8

// f_op_msg_mng
#define fopMsgM_SearchByID_addr 0x8001fa24

// f_pc_searcher
#define fpcSch_JudgeForPName_addr 0x80023578

// d_kankyo
#define g_env_light_addr 0x80426b94

// d_s_play
#define sPauseTimer_addr 0x8044b265

// m_Do_ext
#define mDoExt_getMesgFont_addr 0x800149f0

// m_Do_controller_pad
#define mDoCPd_c__m_gamePad_addr 0x803d7418

// m_Do_mtx
#define mDoMtx_stack_c__now_addr 0x803d75b0
#define mDoMtx_XYZrotM__addr 0x8000c164
#define mDoMtx_stack_c__scaleM_addr 0x8000ce38

#endif

#ifdef WII_NTSCU_10
// System
#define tp_memset_addr 0x8000443c
#define tp_memalign_addr 0x8024df80
#define tp_free_addr 0x8024dfa0
#define tp_osReport_addr 0x800090a8
#define tp_memcpy_addr 0x80004338
#define tp_getLayerNo_addr 0x8002f640
#define tp_getSave_addr 0x8003929c
#define tp_putSave_addr 0x800392cc
#define tp_sprintf_addr 0x803c32e4
#define tp_strcpy_addr 0x803c34f4
#define tp_strlen_addr 0x803bdb38
#define tp_strcmp_addr 0x803c3624

// Math
#define tp_atan_addr 0x803c74e0
#define tp_ceil_addr 0x803c7720
#define tp_copysign_addr 0x803c7860
#define tp_cos_addr 0x803c788c
#define tp_floor_addr 0x803c7960
#define tp_frexp_addr 0x803c7aa4
#define tp_ldexp_addr 0x803c7b2c
#define tp_sin_addr 0x803c7c98
#define tp_tan_addr 0x803c7d70
#define tp_acos_addr 0x803c7de8
#define tp_asin_addr 0x803c7dec
#define tp_atan2_addr 0x803c7df0
#define tp_exp_addr 0x803c7df4
#define tp_fmod_addr 0x803c7df8
#define tp_pow_addr 0x803c7dfc
#define tp_fastSqrt_addr 0x8025ca1c
#define tp_sqrt_addr 0x803c8048
#define tp_sincosTable_addr 0x804c85a0

// Lib
#define cLib_chaseF_addr 0x80259a10
#define cLib_targetAngleY_addr 0x80259ce4
#define cLib_addCalc_addr 0x80259264

// Controller
#define tp_mPadStatus_addr 0x804c2f08
#define tp_mPadButton_addr 0x804c2f38
#define tp_mPadMStick_addr 0x804c2ff8
#define tp_mPadSStick_addr 0x804c3038
#define tp_mPad_addr 0x8044bb60
#define tp_JUTGamePadRead_addr 0x802f4364
#define tp_cPadInfo_addr 0x8044ba60

// TP
#define tp_globalCounters_addr 0x804becb8
#define tp_zelAudio_addr 0x8044a6ac
#define tp_gameInfo_addr 0x80492928
#define tp_sConsole_addr 0x8053a8e0
#define tp_fopScnRq_addr 0x8053a928
#define tp_titleScreenPtr_addr 0x804813e0
#define tp_matrixPtr_addr 0x8047e368
#define tp_rng_addr 0x8053ae58
#define tp_homeMenuSts_addr 0x8053A968

// Items
#define tp_clawshot_addr 0x803e4b5c
#define tp_clawshot_checkbg_addr 0x800fcdbc
#define tp_ironboots_addr 0x803e4990
#define tp_spinner_addr 0x803e4bcc
#define tp_ball_and_chain_addr 0x803e4c0c
#define tp_bottle_addr 0x803e4aa8

// Actor
#define tp_actor_addr 0x8053a9c8
#define tp_actor_stopstatus_addr 0x8053a90c

// Draw
#define tp_draw_addr 0x804bb5d8

// Link
#define tp_link_human_frontroll_addr 0x803e3958
#define tp_link_human_sidestep_addr 0x803e3a00
#define tp_link_human_backjump_addr 0x803e39c8
#define tp_link_human_slide_addr 0x803e3a68
#define tp_link_human_swim_addr 0x803e4ec8
#define tp_link_wolf_general_addr 0x803e4fc4
#define tp_link_wolf_swim_addr 0x803e5a50

// Inventory
#define tp_execItemGet_addr 0x80091d6c

// Scene
#define tp_setTimePass_addr 0x8002be74

// GX
#define GXSetBlendMode_addr 0x803602cc
#define GXBegin_addr 0x8035d1dc
#define GXSetVtxAttrFmt_addr 0x8035c064
#define GXLoadPosMtxImm_addr 0x803608b0
#define GXSetNumIndStages_addr 0x8035f83c
#define GXSetTevDirect_addr 0x8035f85c
#define GXSetAlphaCompare_addr 0x8035fd38
#define GXSetZMode_addr 0x80360374
#define GXSetTevOp_addr 0x8035f8fc
#define GXSetNumChans_addr 0x8035e4a4
#define GXSetNumTevStages_addr 0x8035ff58
#define GXSetNumTexGens_addr 0x8035c6c0
#define GXSetTevOrder_addr 0x8035fdfc
#define GXSetTevColorIn_addr 0x8035f990
#define GXSetTevAlphaIn_addr 0x8035f9d0
#define GXSetTevColorOp_addr 0x8035fa10
#define GXSetTevAlphaOp_addr 0x8035fa68
#define GXSetCullMode_addr 0x8035d4a4
#define GXLoadTexMtxImm_addr 0x80360978
#define GXSetChanCtrl_addr 0x8035e4c8
#define GXSetCurrentMtx_addr 0x80360958
#define GXSetTexCoordGen2_addr 0x8035c498
#define GXSetLineWidth_addr 0x8035d400
#define GXClearVtxDesc_addr 0x8035c030
#define GXSetVtxDesc_addr 0x8035b9e4
#define GXFlush_addr 0x8035c770
#define GXInitTexObj_addr 0x8035e750
#define GXLoadTexObj_addr 0x8035ec94
#define GXInvalidateTexAll_addr 0x8035ee78
#define GXSetProjection_addr 0x803607c0
#define GXSetScissor_addr 0x80360b08
#define GXGetScissor_addr 0x80360b70
#define wgPipe_addr 0xCC008000

// misc functions (sort later)
#define tp_cDyl_InitAsync_addr 0x8001e300
#define tp_fapGm_Execute_addr 0x8001e6b0
#define tp_draw_console_addr 0x802fb3ac
#define tp_PADRead_addr 0x8037a0d0
#define tp_setSpecialGravity_addr 0x800b2898
#define tp_checkCastleTownUseItem_addr 0x800b6d6c
#define tp_query042_addr 0x80238c6c
#define tp_cc_at_check_addr 0x800846b4

// d_bg_s
#define cBgS__GroundCross_addr 0x800724a4

// d_save
#define dSv_player_item_c__setItem_addr 0x80037738
#define dSv_player_item_c__getItem_addr 0x80039ee0
#define dSv_player_item_record_c__setBombNum_addr 0x80038318
#define dSv_player_item_record_c__getBombNum_addr 0x80038324
#define dSv_player_status_a_c__getSelectItemIndex_addr 0x800372c8
#define dSv_player_status_b_c__isTransformLV_addr 0x8003743c
#define dSv_player_status_b_c__onTransformLV_addr 0x80037420
#define dSv_light_drop_c__setLightDropNum_addr 0x80038620
#define dSv_light_drop_c__getLightDropNum_addr 0x80038638
#define dSv_info_c__onSwitch_addr 0x800393f4
#define dSv_info_c__offSwitch_addr 0x800394b4
#define dSv_memBit_c__isSwitch_addr 0x80038ab8
#define dSv_memBit_c__onSwitch_addr 0x80038a68
#define dSv_memBit_c__offSwitch_addr 0x80038a90
#define dSv_memBit_c__isDungeonItem_addr 0x80038b88
#define dSv_memBit_c__onDungeonItem_addr 0x80038b6c
#define dSv_player_get_item_c__onFirstBit_addr 0x80038224
#define dSv_player_get_item_c__offFirstBit_addr 0x80038250
#define dSv_event_c__isEventBit_addr 0x80038bf4
#define dSv_event_c__offEventBit_addr 0x80038bdc
#define dSv_event_c__onEventBit_addr 0x80038bc4
#define dSv_player_get_item_c__isFirstBit_addr 0x8003827c
#define dSv_player_return_place_c__set_addr 0x800374b4

// d_meter2_info
#define g_meter2_info_addr 0x804bcb78

// d_com_inf_game
#define dComIfGs_setSelectItemIndex_addr 0x800323d4
#define dComIfGs_getMixItemIndex_addr 0x800324c0
#define dComIfGs_setMixItemIndex_addr 0x80032418
#define dComIfGs_onZoneSwitch_addr 0x8003207c
#define dComIfGs_onOneZoneSwitch_addr 0x800321b0

// d_stage
#define dStage_nextStage_c__set_addr 0x8002897c

// d_menu_window
#define dMw_c__offMenuRing_addr 0x801e0914
#define dMw_c__key_wait_init_addr 0x801e0960
#define dMw_c__ring_close_proc_addr 0x801e1700
#define dMw_c__ring_open_proc_addr 0x801e1678
#define dMw_c__collect_close_proc_addr 0x801e183c
#define dMw_c__ring_delete_addr 0x801e24fc
#define dMw_c__isEventCheck_addr 0x801e3334
#define dMw_c__execute_addr 0x801e3678
#define dMw_c___delete_addr 0x801e39f8
#define dMw_c__fmap_close_proc_addr 0x801e19f8
#define dMw_c__dmap_close_proc_addr 0x801e1b9c
#define dMw_c__collect_save_close_proc_addr 0x801e1ca0
#define dMw_c__collect_option_close_proc_addr 0x801e1dd0
#define dMw_c__collect_letter_close_proc_addr 0x801e1ed8
#define dMw_c__collect_fishing_close_proc_addr 0x801e1fe0
#define dMw_c__collect_skill_close_proc_addr 0x801e20e8
#define dMw_c__collect_insect_close_proc_addr 0x801e21f0
#define dMw_c__insect_close_proc_addr 0x801e235c

// JKernel
#define JKernel__operator_new_addr 0x802e2b2c
#define JKernel__operator_delete_addr 0x802e2b74
#define JKRArchive__getResource2_addr 0x802e8cac
#define tp_zeldaHeap_addr 0x8053a884
#define tp_gameHeap_addr 0x8053a880
#define tp_archiveHeap_addr 0x8053a88c
#define JKRExpHeap__getUsedSize_addr 0x802e3ba4
#define JKRHeap__getFreeSize_addr 0x802e2680
#define JKRHeap__getTotalFreeSize_addr 0x802e2690
#define JKRExpHeap__do_getTotalFreeSize_addr 0x802e3b40
#define JKRHeap__alloc_addr 0x802e2468

// J3DSys
#define j3dSys_addr 0x804c3620

// J3DPacket
#define J3DDrawBuffer__entryImm_addr 0x8032f8f4
#define J3DPacket__entry_addr 0x80322cf4

// J2DPicture
#define J2DPicture__J2DPicture4_addr 0x8030ef10
#define J2DPicture__draw_addr 0x80310278

// J2DPane
#define J2DPane__J2DPane1_addr 0x80308834

// J2DTextBox
#define J2DTextBox__J2DTextBox1_addr 0x80311cf4
#define J2DTextBox__setFont_addr 0x80312830
#define J2DTextBox__setString_addr 0x80312bc8
#define J2DTextBox__draw2_addr 0x80312a20

// d_a_alink
#define daAlink_c__checkStageName_addr 0x80096734
#define daAlink_c__posMove_addr 0x800b3020

// f_op_actor_mng
#define fopAcM_create_addr 0x8001f868
#define fopAcM_gc_c__gndCheck_addr 0x80023434
#define g_fopAcTg_Queue_addr 0x8047e138
#define fopAcM_gc_c__mGroundY_addr 0x8053a914

// f_op_actor_iter
#define fopAcIt_Judge_addr 0x8001f460

// f_op_msg_mng
#define fopMsgM_SearchByID_addr 0x80024f80

// f_pc_searcher
#define fpcSch_JudgeForPName_addr 0x80028150

// d_kankyo
#define g_env_light_addr 0x804b944c

// d_s_play
#define sPauseTimer_addr 0x8053ae1d

// m_Do_ext
#define mDoExt_getMesgFont_addr 0x800198e4

// m_Do_controller_pad
#define mDoCPd_c__m_gamePad_addr 0x8044ba50

// m_Do_mtx
#define mDoMtx_stack_c__now_addr 0x80453500
#define mDoMtx_XYZrotM__addr 0x8001283c
#define mDoMtx_stack_c__scaleM_addr 0x80013454

#endif

#ifdef WII_PAL
// System
#define tp_memset_addr 0x8000443c
#define tp_memalign_addr 0x8024db10
#define tp_free_addr 0x8024db30
#define tp_osReport_addr 0x800091e0
#define tp_memcpy_addr 0x80004338
#define tp_getLayerNo_addr 0x8002f77c
#define tp_getSave_addr 0x80039518
#define tp_putSave_addr 0x80039548
#define tp_sprintf_addr 0x803ae1a0
#define tp_strcpy_addr 0x803ae3b0
#define tp_strlen_addr 0x803a89f4
#define tp_strcmp_addr 0x803ae4e0

// Math
#define tp_atan_addr 0x803b239c
#define tp_ceil_addr 0x803b25dc
#define tp_copysign_addr 0x803b271c
#define tp_cos_addr 0x803b2748
#define tp_floor_addr 0x803b281c
#define tp_frexp_addr 0x803b2960
#define tp_ldexp_addr 0x803b29e8
#define tp_sin_addr 0x803b2b54
#define tp_tan_addr 0x803b2c2c
#define tp_acos_addr 0x803b2ca4
#define tp_asin_addr 0x803b2ca8
#define tp_atan2_addr 0x803b2cac
#define tp_exp_addr 0x803b2cb0
#define tp_fmod_addr 0x803b2cb4
#define tp_pow_addr 0x803b2cb8
#define tp_fastSqrt_addr 0x8025c5ac
#define tp_sqrt_addr 0x803b2f04
#define tp_sincosTable_addr 0x804aef40

// Lib
#define cLib_chaseF_addr 0x802595a0
#define cLib_targetAngleY_addr 0x80259874
#define cLib_addCalc_addr 0x80258df4

// Controller
#define tp_mPadStatus_addr 0x804a9890
#define tp_mPadButton_addr 0x804a98c0
#define tp_mPadMStick_addr 0x804a9980
#define tp_mPadSStick_addr 0x804a99c0
#define tp_mPad_addr 0x80433a68
#define tp_JUTGamePadRead_addr 0x802df164
#define tp_cPadInfo_addr 0x80433968

// TP
#define tp_globalCounters_addr 0x804a5cf8
#define tp_zelAudio_addr 0x804325ac
#define tp_gameInfo_addr 0x8047a828
#define tp_sConsole_addr 0x805210a8
#define tp_fopScnRq_addr 0x805210f0
#define tp_titleScreenPtr_addr 0x804692e0
#define tp_matrixPtr_addr 0x80466268
#define tp_rng_addr 0x80521638
#define tp_homeMenuSts_addr 0x80521130

// Items
#define tp_clawshot_addr 0x803d0b9c
#define tp_clawshot_checkbg_addr 0x800fd364
#define tp_ironboots_addr 0x803d09d0
#define tp_spinner_addr 0x803d0c0c
#define tp_ball_and_chain_addr 0x803d0c4c
#define tp_bottle_addr 0x803d0ae8

// Actor
#define tp_actor_addr 0x80521190
#define tp_actor_stopstatus_addr 0x805210d4

// Draw
#define tp_draw_addr 0x804a34f8

// Link
#define tp_link_human_frontroll_addr 0x803cf998
#define tp_link_human_sidestep_addr 0x803cfa40
#define tp_link_human_backjump_addr 0x803cfa08
#define tp_link_human_slide_addr 0x803cfaa8
#define tp_link_human_swim_addr 0x803d0f08
#define tp_link_wolf_general_addr 0x803d1004
#define tp_link_wolf_swim_addr 0x803d1a90

// Inventory
#define tp_execItemGet_addr 0x800920d8

// Scene
#define tp_setTimePass_addr 0x8002bfb0

// GX
#define GXSetBlendMode_addr 0x8034b134
#define GXBegin_addr 0x80348044
#define GXSetVtxAttrFmt_addr 0x80346ecc
#define GXLoadPosMtxImm_addr 0x8034b718
#define GXSetNumIndStages_addr 0x8034a6a4
#define GXSetTevDirect_addr 0x8034a6c4
#define GXSetAlphaCompare_addr 0x8034aba0
#define GXSetZMode_addr 0x8034b1dc
#define GXSetTevOp_addr 0x8034a764
#define GXSetNumChans_addr 0x8034930c
#define GXSetNumTevStages_addr 0x8034adc0
#define GXSetNumTexGens_addr 0x80347528
#define GXSetTevOrder_addr 0x8034ac64
#define GXSetTevColorIn_addr 0x8034a7f8
#define GXSetTevAlphaIn_addr 0x8034a838
#define GXSetTevColorOp_addr 0x8034a878
#define GXSetTevAlphaOp_addr 0x8034a8d0
#define GXSetCullMode_addr 0x8034830c
#define GXLoadTexMtxImm_addr 0x8034b7e0
#define GXSetChanCtrl_addr 0x80349330
#define GXSetCurrentMtx_addr 0x8034b7c0
#define GXSetTexCoordGen2_addr 0x80347300
#define GXSetLineWidth_addr 0x80348268
#define GXClearVtxDesc_addr 0x80346e98
#define GXSetVtxDesc_addr 0x8034684c
#define GXFlush_addr 0x803475d8
#define GXInitTexObj_addr 0x803495b8
#define GXLoadTexObj_addr 0x80349afc
#define GXInvalidateTexAll_addr 0x80349ce0
#define GXSetProjection_addr 0x8034b628
#define GXSetScissor_addr 0x8034b970
#define GXGetScissor_addr 0x8034b9d8
#define wgPipe_addr 0xCC008000

// misc functions (sort later)
#define tp_cDyl_InitAsync_addr 0x8001e4b8
#define tp_fapGm_Execute_addr 0x8001e868
#define tp_draw_console_addr 0x802e61ac
#define tp_PADRead_addr 0x80364f8c
#define tp_setSpecialGravity_addr 0x800b2d2c
#define tp_checkCastleTownUseItem_addr 0x800b7210
#define tp_query042_addr 0x802383bc
#define tp_cc_at_check_addr 0x80084a40

// d_bg_s
#define cBgS__GroundCross_addr 0x80072758

// d_save
#define dSv_player_item_c__setItem_addr 0x80037904
#define dSv_player_item_c__getItem_addr 0x8003a15c
#define dSv_player_item_record_c__setBombNum_addr 0x800384e4
#define dSv_player_item_record_c__getBombNum_addr 0x800384f0
#define dSv_player_status_a_c__getSelectItemIndex_addr 0x80037494
#define dSv_player_status_b_c__isTransformLV_addr 0x80037608
#define dSv_player_status_b_c__onTransformLV_addr 0x800375ec
#define dSv_light_drop_c__setLightDropNum_addr 0x800387ec
#define dSv_light_drop_c__getLightDropNum_addr 0x80038804
#define dSv_info_c__onSwitch_addr 0x80039670
#define dSv_info_c__offSwitch_addr 0x80039730
#define dSv_memBit_c__isSwitch_addr 0x80038d34
#define dSv_memBit_c__onSwitch_addr 0x80038ce4
#define dSv_memBit_c__offSwitch_addr 0x80038d0c
#define dSv_memBit_c__isDungeonItem_addr 0x80038e04
#define dSv_memBit_c__onDungeonItem_addr 0x80038de8
#define dSv_player_get_item_c__onFirstBit_addr 0x800383f0
#define dSv_player_get_item_c__offFirstBit_addr 0x8003841c
#define dSv_event_c__isEventBit_addr 0x80038e70
#define dSv_event_c__offEventBit_addr 0x80038e58
#define dSv_event_c__onEventBit_addr 0x80038e40
#define dSv_player_get_item_c__isFirstBit_addr 0x80038448
#define dSv_player_return_place_c__set_addr 0x80037680

// d_meter2_info
#define g_meter2_info_addr 0x804a4ab8

// d_com_inf_game
#define dComIfGs_setSelectItemIndex_addr 0x80032590
#define dComIfGs_getMixItemIndex_addr 0x8003267c
#define dComIfGs_setMixItemIndex_addr 0x800325d4
#define dComIfGs_onZoneSwitch_addr 0x800338ac
#define dComIfGs_onOneZoneSwitch_addr 0x800339e0

// d_stage
#define dStage_nextStage_c__set_addr 0x80028b40

// d_menu_window
#define dMw_c__offMenuRing_addr 0x801dfd40
#define dMw_c__key_wait_init_addr 0x801dfd8c
#define dMw_c__ring_close_proc_addr 0x801e0b2c
#define dMw_c__ring_open_proc_addr 0x801e0aa4
#define dMw_c__collect_close_proc_addr 0x801e0c68
#define dMw_c__ring_delete_addr 0x801e1928
#define dMw_c__isEventCheck_addr 0x801e2760
#define dMw_c__execute_addr 0x801e2aa4
#define dMw_c___delete_addr 0x801e2e24
#define dMw_c__fmap_close_proc_addr 0x801e0e24
#define dMw_c__dmap_close_proc_addr 0x801e0fc8
#define dMw_c__collect_save_close_proc_addr 0x801e10cc
#define dMw_c__collect_option_close_proc_addr 0x801e11fc
#define dMw_c__collect_letter_close_proc_addr 0x801e1304
#define dMw_c__collect_fishing_close_proc_addr 0x801e140c
#define dMw_c__collect_skill_close_proc_addr 0x801e1514
#define dMw_c__collect_insect_close_proc_addr 0x801e161c
#define dMw_c__insect_close_proc_addr 0x801e1788

// JKernel
#define JKernel__operator_new_addr 0x802cd92c
#define JKernel__operator_delete_addr 0x802cd974
#define JKRArchive__getResource2_addr 0x802d49a0
#define tp_zeldaHeap_addr 0x80521044
#define tp_gameHeap_addr 0x80521040
#define tp_archiveHeap_addr 0x8052104c
#define JKRExpHeap__getUsedSize_addr 0x802ce9a4
#define JKRHeap__getFreeSize_addr 0x802cd480
#define JKRHeap__getTotalFreeSize_addr 0x802cd490
#define JKRExpHeap__do_getTotalFreeSize_addr 0x802ce940
#define JKRHeap__alloc_addr 0x802cd268

// J3DSys
#define j3dSys_addr 0x804a9fc0

// J3DPacket
#define J3DDrawBuffer__entryImm_addr 0x8031a6f4
#define J3DPacket__entry_addr 0x8030daf4

// J2DPicture
#define J2DPicture__J2DPicture4_addr 0x802f9d10
#define J2DPicture__draw_addr 0x802fb078

// J2DPane
#define J2DPane__J2DPane1_addr 0x802f3634

// J2DTextBox
#define J2DTextBox__J2DTextBox1_addr 0x802fcaf4
#define J2DTextBox__setFont_addr 0x802fd630
#define J2DTextBox__setString_addr 0x802fd9c8
#define J2DTextBox__draw2_addr 0x802fd820

// d_a_alink
#define daAlink_c__checkStageName_addr 0x80098268
#define daAlink_c__posMove_addr 0x800b34b4

// f_op_actor_mng
#define fopAcM_create_addr 0x80021024
#define fopAcM_gc_c__gndCheck_addr 0x800235f8
#define g_fopAcTg_Queue_addr 0x80466038
#define fopAcM_gc_c__mGroundY_addr 0x805210dc

// f_op_actor_iter
#define fopAcIt_Judge_addr 0x80020c1c

// f_op_msg_mng
#define fopMsgM_SearchByID_addr 0x80025144

// f_pc_searcher
#define fpcSch_JudgeForPName_addr 0x80029944

// d_kankyo
#define g_env_light_addr 0x8047b274

// d_s_play
#define sPauseTimer_addr 0x805215f5

// m_Do_ext
#define mDoExt_getMesgFont_addr 0x8001998c

// m_Do_controller_pad
#define mDoCPd_c__m_gamePad_addr 0x80433958

// m_Do_mtx
#define mDoMtx_stack_c__now_addr 0x8043b408
#define mDoMtx_XYZrotM__addr 0x800128dc
#define mDoMtx_stack_c__scaleM_addr 0x800134f4

#endif

#ifdef WII_NTSCU_12
// System
#define tp_memset_addr 0x8000443c
#define tp_memalign_addr 0x8024d6a8
#define tp_free_addr 0x8024d6c8
#define tp_osReport_addr 0x80009218
#define tp_memcpy_addr 0x80004338
#define tp_getLayerNo_addr 0x8002f6c8
#define tp_getSave_addr 0x8003944c
#define tp_putSave_addr 0x8003947c
#define tp_sprintf_addr 0x803add1c
#define tp_strcpy_addr 0x803adf2c
#define tp_strlen_addr 0x803a8570
#define tp_strcmp_addr 0x803ae05c

// Math
#define tp_atan_addr 0x803b1f18
#define tp_ceil_addr 0x803b2158
#define tp_copysign_addr 0x803b2298
#define tp_cos_addr 0x803b22c4
#define tp_floor_addr 0x803b2398
#define tp_frexp_addr 0x803b24dc
#define tp_ldexp_addr 0x803b2564
#define tp_sin_addr 0x803b26d0
#define tp_tan_addr 0x803b27a8
#define tp_acos_addr 0x803b2820
#define tp_asin_addr 0x803b2824
#define tp_atan2_addr 0x803b2828
#define tp_exp_addr 0x803b282c
#define tp_fmod_addr 0x803b2830
#define tp_pow_addr 0x803b2834
#define tp_fastSqrt_addr 0x8025c144
#define tp_sqrt_addr 0x803b2a80
#define tp_sincosTable_addr 0x804ae620

// Lib
#define cLib_chaseF_addr 0x80259138
#define cLib_targetAngleY_addr 0x8025940c
#define cLib_addCalc_addr 0x8025898c

// Controller
#define tp_mPadStatus_addr 0x804a8f70
#define tp_mPadButton_addr 0x804a8fa0
#define tp_mPadMStick_addr 0x804a9060
#define tp_mPadSStick_addr 0x804a90a0
#define tp_mPad_addr 0x80433168
#define tp_JUTGamePadRead_addr 0x802ded34
#define tp_cPadInfo_addr 0x80433068

// TP
#define tp_globalCounters_addr 0x804a53e0
#define tp_zelAudio_addr 0x80431cac
#define tp_gameInfo_addr 0x80479f30
#define tp_sConsole_addr 0x805208e8
#define tp_fopScnRq_addr 0x80520930
#define tp_titleScreenPtr_addr 0x804689e8
#define tp_matrixPtr_addr 0x80465970
#define tp_rng_addr 0x80520e78
#define tp_homeMenuSts_addr 0x80520970

// Items
#define tp_clawshot_addr 0x803cfe5c
#define tp_clawshot_checkbg_addr 0x800fd338
#define tp_ironboots_addr 0x803cfc90
#define tp_spinner_addr 0x803cfecc
#define tp_ball_and_chain_addr 0x803cff0c
#define tp_bottle_addr 0x803cfda8

// Actor
#define tp_actor_addr 0x805209d0
#define tp_actor_stopstatus_addr 0x80520914

// Draw
#define tp_draw_addr 0x804a2be0

// Link
#define tp_link_human_frontroll_addr 0x803cec58
#define tp_link_human_sidestep_addr 0x803ced00
#define tp_link_human_backjump_addr 0x803cecc8
#define tp_link_human_slide_addr 0x803ced68
#define tp_link_human_swim_addr 0x803d01c8
#define tp_link_wolf_general_addr 0x803d02c4
#define tp_link_wolf_swim_addr 0x803d0d50

// Inventory
#define tp_execItemGet_addr 0x80092070

// Scene
#define tp_setTimePass_addr 0x8002befc

// GX
#define GXSetBlendMode_addr 0x8034ad04
#define GXBegin_addr 0x80347c14
#define GXSetVtxAttrFmt_addr 0x80346a9c
#define GXLoadPosMtxImm_addr 0x8034b2e8
#define GXSetNumIndStages_addr 0x8034a274
#define GXSetTevDirect_addr 0x8034a294
#define GXSetAlphaCompare_addr 0x8034a770
#define GXSetZMode_addr 0x8034adac
#define GXSetTevOp_addr 0x8034a334
#define GXSetNumChans_addr 0x80348edc
#define GXSetNumTevStages_addr 0x8034a990
#define GXSetNumTexGens_addr 0x803470f8
#define GXSetTevOrder_addr 0x8034a834
#define GXSetTevColorIn_addr 0x8034a3c8
#define GXSetTevAlphaIn_addr 0x8034a408
#define GXSetTevColorOp_addr 0x8034a448
#define GXSetTevAlphaOp_addr 0x8034a4a0
#define GXSetCullMode_addr 0x80347edc
#define GXLoadTexMtxImm_addr 0x8034b3b0
#define GXSetChanCtrl_addr 0x80348f00
#define GXSetCurrentMtx_addr 0x8034b390
#define GXSetTexCoordGen2_addr 0x80346ed0
#define GXSetLineWidth_addr 0x80347e38
#define GXClearVtxDesc_addr 0x80346a68
#define GXSetVtxDesc_addr 0x8034641c
#define GXFlush_addr 0x803471a8
#define GXInitTexObj_addr 0x80349188
#define GXLoadTexObj_addr 0x803496cc
#define GXInvalidateTexAll_addr 0x803498b0
#define GXSetProjection_addr 0x8034b1f8
#define GXSetScissor_addr 0x8034b540
#define GXGetScissor_addr 0x8034b5a8
#define wgPipe_addr 0xCC008000

// misc functions (sort later)
#define tp_cDyl_InitAsync_addr 0x8001e3ec
#define tp_fapGm_Execute_addr 0x8001e79c
#define tp_draw_console_addr 0x802e5d7c
#define tp_PADRead_addr 0x80364b08
#define tp_setSpecialGravity_addr 0x800b2cf0
#define tp_checkCastleTownUseItem_addr 0x800b71d4
#define tp_query042_addr 0x80238468
#define tp_cc_at_check_addr 0x800849d8

// d_bg_s
#define cBgS__GroundCross_addr 0x800726f0

// d_save
#define dSv_player_item_c__setItem_addr 0x80037850
#define dSv_player_item_c__getItem_addr 0x8003a090
#define dSv_player_item_record_c__setBombNum_addr 0x80038430
#define dSv_player_item_record_c__getBombNum_addr 0x8003843c
#define dSv_player_status_a_c__getSelectItemIndex_addr 0x800373e0
#define dSv_player_status_b_c__isTransformLV_addr 0x80037554
#define dSv_player_status_b_c__onTransformLV_addr 0x80037538
#define dSv_light_drop_c__setLightDropNum_addr 0x80038738
#define dSv_light_drop_c__getLightDropNum_addr 0x80038750
#define dSv_info_c__onSwitch_addr 0x800395a4
#define dSv_info_c__offSwitch_addr 0x80039664
#define dSv_memBit_c__isSwitch_addr 0x80038c68
#define dSv_memBit_c__onSwitch_addr 0x80038c18
#define dSv_memBit_c__offSwitch_addr 0x80038c40
#define dSv_memBit_c__isDungeonItem_addr 0x80038d38
#define dSv_memBit_c__onDungeonItem_addr 0x80038d1c
#define dSv_player_get_item_c__onFirstBit_addr 0x8003833c
#define dSv_player_get_item_c__offFirstBit_addr 0x80038368
#define dSv_event_c__isEventBit_addr 0x80038da4
#define dSv_event_c__offEventBit_addr 0x80038d8c
#define dSv_event_c__onEventBit_addr 0x80038d74
#define dSv_player_get_item_c__isFirstBit_addr 0x80038394
#define dSv_player_return_place_c__set_addr 0x800375cc

// d_meter2_info
#define g_meter2_info_addr 0x804a41a0

// d_com_inf_game
#define dComIfGs_setSelectItemIndex_addr 0x800324dc
#define dComIfGs_getMixItemIndex_addr 0x800325c8
#define dComIfGs_setMixItemIndex_addr 0x80032520
#define dComIfGs_onZoneSwitch_addr 0x80032184
#define dComIfGs_onOneZoneSwitch_addr 0x800322b8

// d_stage
#define dStage_nextStage_c__set_addr 0x80028a8c

// d_menu_window
#define dMw_c__offMenuRing_addr 0x801e0010
#define dMw_c__key_wait_init_addr 0x801e005c
#define dMw_c__ring_close_proc_addr 0x801e0e24
#define dMw_c__ring_open_proc_addr 0x801e0d9c
#define dMw_c__collect_close_proc_addr 0x801e0f60
#define dMw_c__ring_delete_addr 0x801e1c20
#define dMw_c__isEventCheck_addr 0x801e2a58
#define dMw_c__execute_addr 0x801e2d9c
#define dMw_c___delete_addr 0x801e311c
#define dMw_c__fmap_close_proc_addr 0x801e111c
#define dMw_c__dmap_close_proc_addr 0x801e12c0
#define dMw_c__collect_save_close_proc_addr 0x801e13c4
#define dMw_c__collect_option_close_proc_addr 0x801e14f4
#define dMw_c__collect_letter_close_proc_addr 0x801e15fc
#define dMw_c__collect_fishing_close_proc_addr 0x801e1704
#define dMw_c__collect_skill_close_proc_addr 0x801e180c
#define dMw_c__collect_insect_close_proc_addr 0x801e1914
#define dMw_c__insect_close_proc_addr 0x801e1a80

// JKernel
#define JKernel__operator_new_addr 0x802cd4fc
#define JKRArchive__getResource2_addr 0x802d367c

// J2DPicture
#define J2DPicture__J2DPicture4_addr 0x802f98e0
#define J2DPicture__draw_addr 0x802fac48

// d_a_alink
#define daAlink_c__checkStageName_addr 0x80096b4c
#define daAlink_c__posMove_addr 0x800b3478

// f_op_actor_mng
#define fopAcM_create_addr 0x8001f954
#define fopAcM_gc_c__gndCheck_addr 0x8002352c
#define g_fopAcTg_Queue_addr 0x80465740
#define fopAcM_gc_c__mGroundY_addr 0x8052091c

// f_op_actor_iter
#define fopAcIt_Judge_addr 0x8001f54c

// f_op_msg_mng
#define fopMsgM_SearchByID_addr 0x80025078

// f_pc_searcher
#define fpcSch_JudgeForPName_addr 0x80028260

// d_kankyo
#define g_env_light_addr 0x804a0a54

#endif
#endif  // !REL_MODULE

#endif  // LIB_TP_ADDRS