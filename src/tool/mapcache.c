/****************************************************************************!
*                _           _   _   _                                       *
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *
*                                                                            *
*                            www.brathena.org                                *
******************************************************************************
* src/tool/mapcache.c                                                        *
* Respons�vel pelo cache de mapas adicionados ao emulador                    *
******************************************************************************
* Copyright (c) brAthena Dev Team                                            *
* Copyright (c) Hercules Dev Team                                            *
* Copyright (c) Athena Dev Teams                                             *
*                                                                            *
* Licenciado sob a licenca GNU GPL                                           *
* Para mais informa��es leia o arquivo LICENSE na ra�z do emulador           *
*****************************************************************************/

#define BRATHENA_CORE

#include "common/cbasetypes.h"
#include "common/core.h"
#include "common/grfio.h"
#include "common/memmgr.h"
#include "common/mmo.h"
#include "common/showmsg.h"
#include "common/strlib.h"
#include "common/utils.h"

#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#define NO_WATER 1000000

const char *map_list[] = {
	"alb_ship",
	"alb2trea",
	"alberta",
	"alberta_in",
	"alde_dun01",
	"alde_dun02",
	"alde_dun03",
	"alde_dun04",
	"aldeba_in",
	"aldebaran",
	"anthell01",
	"anthell02",
	"arena_room",
	"c_tower1",
	"c_tower2",
	"c_tower3",
	"c_tower4",
	"force_1-1",
	"force_1-2",
	"force_1-3",
	"force_2-1",
	"force_2-2",
	"force_2-3",
	"force_3-1",
	"force_3-2",
	"force_3-3",
	"gef_dun00",
	"gef_dun01",
	"gef_dun02",
	"gef_dun03",
	"gef_fild00",
	"gef_fild01",
	"gef_fild02",
	"gef_fild03",
	"gef_fild04",
	"gef_fild05",
	"gef_fild06",
	"gef_fild07",
	"gef_fild08",
	"gef_fild09",
	"gef_fild10",
	"gef_fild11",
	"gef_fild12",
	"gef_fild13",
	"gef_fild14",
	"gef_tower",
	"geffen",
	"geffen_in",
	"gl_cas01",
	"gl_cas02",
	"gl_church",
	"gl_chyard",
	"gl_dun01",
	"gl_dun02",
	"gl_in01",
	"gl_knt01",
	"gl_knt02",
	"gl_prison",
	"gl_prison1",
	"gl_sew01",
	"gl_sew02",
	"gl_sew03",
	"gl_sew04",
	"gl_step",
	"glast_01",
	"hunter_1-1",
	"hunter_2-1",
	"hunter_3-1",
	"in_hunter",
	"in_moc_16",
	"in_orcs01",
	"in_sphinx1",
	"in_sphinx2",
	"in_sphinx3",
	"in_sphinx4",
	"in_sphinx5",
	"iz_dun00",
	"iz_dun01",
	"iz_dun02",
	"iz_dun03",
	"iz_dun04",
	"job_sword1",
	"izlu2dun",
	"izlude",
	"izlude_in",
	"job_thief1",
	"knight_1-1",
	"knight_2-1",
	"knight_3-1",
	"mjo_dun01",
	"mjo_dun02",
	"mjo_dun03",
	"mjolnir_01",
	"mjolnir_02",
	"mjolnir_03",
	"mjolnir_04",
	"mjolnir_05",
	"mjolnir_06",
	"mjolnir_07",
	"mjolnir_08",
	"mjolnir_09",
	"mjolnir_10",
	"mjolnir_11",
	"mjolnir_12",
	"moc_castle",
	"moc_fild01",
	"moc_fild02",
	"moc_fild03",
	"moc_fild04",
	"moc_fild05",
	"moc_fild06",
	"moc_fild07",
	"moc_fild08",
	"moc_fild09",
	"moc_fild10",
	"moc_fild11",
	"moc_fild12",
	"moc_fild13",
	"moc_fild14",
	"moc_fild15",
	"moc_fild16",
	"moc_fild17",
	"moc_fild18",
	"moc_fild19",
	"moc_pryd01",
	"moc_pryd02",
	"moc_pryd03",
	"moc_pryd04",
	"moc_pryd05",
	"moc_pryd06",
	"moc_prydb1",
	"moc_ruins",
	"monk_in",
	"morocc",
	"morocc_in",
	"new_1-1",
	"new_1-2",
	"new_1-3",
	"new_1-4",
	"new_2-1",
	"new_2-2",
	"new_2-3",
	"new_2-4",
	"new_3-1",
	"new_3-2",
	"new_3-3",
	"new_3-4",
	"new_4-1",
	"new_4-2",
	"new_4-3",
	"new_4-4",
	"new_5-1",
	"new_5-2",
	"new_5-3",
	"new_5-4",
	"orcsdun01",
	"orcsdun02",
	"ordeal_1-1",
	"ordeal_1-2",
	//"ordeal_1-3",
	//"ordeal_1-4",
	"ordeal_2-1",
	"ordeal_2-2",
	//"ordeal_2-3",
	//"ordeal_2-4",
	"ordeal_3-1",
	"ordeal_3-2",
	//"ordeal_3-3",
	//"ordeal_3-4",
	"pay_arche",
	"pay_dun00",
	"pay_dun01",
	"pay_dun02",
	"pay_dun03",
	"pay_dun04",
	"pay_fild01",
	"pay_fild02",
	"pay_fild03",
	"pay_fild04",
	"pay_fild05",
	"pay_fild06",
	"pay_fild07",
	"pay_fild08",
	"pay_fild09",
	"pay_fild10",
	"pay_fild11",
	"payon",
	"payon_in01",
	"payon_in02",
	"priest_1-1",
	"priest_2-1",
	"priest_3-1",
	"prontera",
	"prt_are_in",
	"prt_are01",
	"pvp_room",
	"prt_castle",
	"prt_church",
	"prt_fild00",
	"prt_fild01",
	"prt_fild02",
	"prt_fild03",
	"prt_fild04",
	"prt_fild05",
	"prt_fild06",
	"prt_fild07",
	"prt_fild08",
	"prt_fild09",
	"prt_fild10",
	"prt_fild11",
	"prt_in",
	"prt_maze01",
	"prt_maze02",
	"prt_maze03",
	"prt_monk",
	"prt_sewb1",
	"prt_sewb2",
	"prt_sewb3",
	"prt_sewb4",
	"pvp_2vs2",
	"pvp_c_room",
	"pvp_n_1-1",
	"pvp_n_1-2",
	"pvp_n_1-3",
	"pvp_n_1-4",
	"pvp_n_1-5",
	"pvp_n_2-1",
	"pvp_n_2-2",
	"pvp_n_2-3",
	"pvp_n_2-4",
	"pvp_n_2-5",
	"pvp_n_3-1",
	"pvp_n_3-2",
	"pvp_n_3-3",
	"pvp_n_3-4",
	"pvp_n_3-5",
	"pvp_n_4-1",
	"pvp_n_4-2",
	"pvp_n_4-3",
	"pvp_n_4-4",
	"pvp_n_4-5",
	"pvp_n_5-1",
	"pvp_n_5-2",
	"pvp_n_5-3",
	"pvp_n_5-4",
	"pvp_n_5-5",
	"pvp_n_6-1",
	"pvp_n_6-2",
	"pvp_n_6-3",
	"pvp_n_6-4",
	"pvp_n_6-5",
	"pvp_n_7-1",
	"pvp_n_7-2",
	"pvp_n_7-3",
	"pvp_n_7-4",
	"pvp_n_7-5",
	"pvp_n_8-1",
	"pvp_n_8-2",
	"pvp_n_8-3",
	"pvp_n_8-4",
	"pvp_n_8-5",
	"pvp_n_room",
	"pvp_y_1-1",
	"pvp_y_1-2",
	"pvp_y_1-3",
	"pvp_y_1-4",
	"pvp_y_1-5",
	"pvp_y_2-1",
	"pvp_y_2-2",
	"pvp_y_2-3",
	"pvp_y_2-4",
	"pvp_y_2-5",
	"pvp_y_3-1",
	"pvp_y_3-2",
	"pvp_y_3-3",
	"pvp_y_3-4",
	"pvp_y_3-5",
	"pvp_y_4-1",
	"pvp_y_4-2",
	"pvp_y_4-3",
	"pvp_y_4-4",
	"pvp_y_4-5",
	"pvp_y_5-1",
	"pvp_y_5-2",
	"pvp_y_5-3",
	"pvp_y_5-4",
	"pvp_y_5-5",
	"pvp_y_6-1",
	"pvp_y_6-2",
	"pvp_y_6-3",
	"pvp_y_6-4",
	"pvp_y_6-5",
	"pvp_y_7-1",
	"pvp_y_7-2",
	"pvp_y_7-3",
	"pvp_y_7-4",
	"pvp_y_7-5",
	"pvp_y_8-1",
	"pvp_y_8-2",
	"pvp_y_8-3",
	"pvp_y_8-4",
	"pvp_y_8-5",
	"pvp_y_room",
	"sword_1-1",
	"sword_2-1",
	"sword_3-1",
	"treasure01",
	"treasure02",
	"wizard_1-1",
	"wizard_2-1",
	"wizard_3-1",
	"xmas",
	"xmas_dun01",
	"xmas_dun02",
	"xmas_fild01",
	"xmas_in",
	"beach_dun",
	"beach_dun2",
	"beach_dun3",
	"cmd_fild01",
	"cmd_fild02",
	"cmd_fild03",
	"cmd_fild04",
	"cmd_fild05",
	"cmd_fild06",
	"cmd_fild07",
	"cmd_fild08",
	"cmd_fild09",
	"cmd_in01",
	"cmd_in02",
	"comodo",
	"quiz_00",
	"quiz_01",
	"g_room1-1",
	"g_room1-2",
	"g_room1-3",
	"g_room2",
	"tur_dun01",
	"tur_dun02",
	"tur_dun03",
	"tur_dun04",
	"tur_dun05",
	"tur_dun06",
	"alde_gld",
	"aldeg_cas01",
	"aldeg_cas02",
	"aldeg_cas03",
	"aldeg_cas04",
	"aldeg_cas05",
	"gefg_cas01",
	"gefg_cas02",
	"gefg_cas03",
	"gefg_cas04",
	"gefg_cas05",
	"gld_dun01",
	"gld_dun02",
	"gld_dun03",
	"gld_dun04",
	"guild_room",
	"guild_vs1",
	"guild_vs2",
	"guild_vs3",
	"guild_vs4",
	"guild_vs5",
	"guild_vs1-1",
	"guild_vs1-2",
	"guild_vs1-3",
	"guild_vs1-4",
	"guild_vs2-1",
	"guild_vs2-2",
	"job_hunte",
	"job_knt",
	"job_prist",
	"job_wiz",
	"pay_gld",
	"payg_cas01",
	"payg_cas02",
	"payg_cas03",
	"payg_cas04",
	"payg_cas05",
	"prt_gld",
	"prtg_cas01",
	"prtg_cas02",
	"prtg_cas03",
	"prtg_cas04",
	"prtg_cas05",
	"alde_alche",
	"in_rogue",
	"job_cru",
	"job_duncer",
	"job_monk",
	"job_sage",
	"mag_dun01",
	"mag_dun02",
	"monk_test",
	"quiz_test",
	"yuno",
	"yuno_fild01",
	"yuno_fild02",
	"yuno_fild03",
	"yuno_fild04",
	"yuno_in01",
	"yuno_in02",
	"yuno_in03",
	"yuno_in04",
	"yuno_in05",
	"ama_dun01",
	"ama_dun02",
	"ama_dun03",
	"ama_fild01",
	"ama_in01",
	"ama_in02",
	"ama_test",
	"amatsu",
	"gon_dun01",
	"gon_dun02",
	"gon_dun03",
	"gon_fild01",
	"gon_in",
	"gon_test",
	"gonryun",
	"sec_in01",
	"sec_in02",
	"sec_pri",
	"umbala",
	"um_dun01",
	"um_dun02",
	"um_fild01",
	"um_fild02",
	"um_fild03",
	"um_fild04",
	"um_in",
	"niflheim",
	"nif_fild01",
	"nif_fild02",
	"nif_in",
	"yggdrasil01",
	"valkyrie",
	"himinn",
	"lou_in01",
	"lou_in02",
	"lou_dun03",
	"lou_dun02",
	"lou_dun01",
	"lou_fild01",
	"louyang",
	"siege_test",
	"n_castle",
	"nguild_gef",
	"nguild_prt",
	"nguild_pay",
	"nguild_alde",
	"jawaii",
	"jawaii_in",
	"gefenia01",
	"gefenia02",
	"gefenia03",
	"gefenia04",
	"new_zone01",
	"new_zone02",
	"new_zone03",
	"new_zone04",
	"payon_in03",
	"ayothaya",
	"ayo_in01",
	"ayo_in02",
	"ayo_fild01",
	"ayo_fild02",
	"ayo_dun01",
	"ayo_dun02",
	"que_god01",
	"que_god02",
	"yuno_fild05",
	"yuno_fild07",
	"yuno_fild08",
	"yuno_fild09",
	"yuno_fild11",
	"yuno_fild12",
	"alde_tt02",
	"turbo_n_1",
	"turbo_n_4",
	"turbo_n_8",
	"turbo_n_16",
	"turbo_e_4",
	"turbo_e_8",
	"turbo_e_16",
	"turbo_room",
	"airplane",
	"airport",
	"einbech",
	"einbroch",
	"ein_dun01",
	"ein_dun02",
	"ein_fild06",
	"ein_fild07",
	"ein_fild08",
	"ein_fild09",
	"ein_fild10",
	"ein_in01",
	"que_sign01",
	"que_sign02",
	"ein_fild03",
	"ein_fild04",
	"lhz_fild02",
	"lhz_fild03",
	"yuno_pre",
	"lhz_fild01",
	"lighthalzen",
	"lhz_in01",
	"lhz_in02",
	"lhz_in03",
	"lhz_que01",
	"lhz_dun01",
	"lhz_dun02",
	"lhz_dun03",
	"lhz_cube",
	"juperos_01",
	"juperos_02",
	"jupe_area1",
	"jupe_area2",
	"jupe_core",
	"jupe_ele",
	"jupe_ele_r",
	"jupe_gate",
	"y_airport",
	"lhz_airport",
	"airplane_01",
	"jupe_cave",
	"quiz_02",
	"hu_fild07",
	"hu_fild05",
	"hu_fild04",
	"hu_fild01",
	"yuno_fild06",
	"job_soul",
	"job_star",
	"que_job01",
	"que_job02",
	"que_job03",
	"abyss_01",
	"abyss_02",
	"abyss_03",
	"thana_step",
	"thana_boss",
	"tha_scene01",
	"tha_t01",
	"tha_t02",
	"tha_t03",
	"tha_t04",
	"tha_t07",
	"tha_t05",
	"tha_t06",
	"tha_t08",
	"tha_t09",
	"tha_t10",
	"tha_t11",
	"tha_t12",
	"auction_01",
	"auction_02",
	"hugel",
	"hu_in01",
	"que_bingo",
	"que_hugel",
	"p_track01",
	"p_track02",
	"odin_tem01",
	"odin_tem02",
	"odin_tem03",
	"hu_fild02",
	"hu_fild03",
	"hu_fild06",
	"ein_fild01",
	"ein_fild02",
	"ein_fild05",
	"yuno_fild10",
	"kh_kiehl02",
	"kh_kiehl01",
	"kh_dun02",
	"kh_dun01",
	"kh_mansion",
	"kh_rossi",
	"kh_school",
	"kh_vila",
	"force_map1",
	"force_map2",
	"force_map3",
	"job_hunter",
	"job_knight",
	"job_priest",
	"job_wizard",
	"ve_in02",
	"rachel",
	"ra_in01",
	"ra_fild01",
	"ra_fild02",
	"ra_fild03",
	"ra_fild04",
	"ra_fild05",
	"ra_fild06",
	"ra_fild07",
	"ra_fild08",
	"ra_fild09",
	"ra_fild10",
	"ra_fild11",
	"ra_fild12",
	"ra_fild13",
	"ra_san01",
	"ra_san02",
	"ra_san03",
	"ra_san04",
	"ra_san05",
	"ra_temin",
	"ra_temple",
	"ra_temsky",
	"que_rachel",
	"ice_dun01",
	"ice_dun02",
	"ice_dun03",
	"ice_dun04",
	"que_thor",
	"thor_camp",
	"thor_v01",
	"thor_v02",
	"thor_v03",
	"veins",
	"ve_in",
	"ve_fild01",
	"ve_fild02",
	"ve_fild03",
	"ve_fild04",
	"ve_fild05",
	"ve_fild06",
	"ve_fild07",
	"poring_c01",
	"poring_c02",
	"que_ng",
	"nameless_i",
	"nameless_n",
	"nameless_in",
	"abbey01",
	"abbey02",
	"abbey03",
	"poring_w01",
	"poring_w02",
	"que_san04",
	"moscovia",
	"mosk_in",
	"mosk_ship",
	"mosk_fild01",
	"mosk_fild02",
	"mosk_dun01",
	"mosk_dun02",
	"mosk_dun03",
	"mosk_que",
	"force_4-1",
	"force_5-1",
	"06guild_r",
	"06guild_01",
	"06guild_02",
	"06guild_03",
	"06guild_04",
	"06guild_05",
	"06guild_06",
	"06guild_07",
	"06guild_08",
	"z_agit",
	"que_temsky",
	"itemmall",
	"bossnia_01",
	"bossnia_02",
	"bossnia_03",
	"bossnia_04",
	"schg_cas01",
	"schg_cas02",
	"schg_cas03",
	"schg_cas04",
	"schg_cas05",
	"sch_gld",
	"cave",
	"moc_fild20",
	"moc_fild21",
	"moc_fild22",
	"que_ba",
	"que_moc_16",
	"que_moon",
	"arug_cas01",
	"arug_cas02",
	"arug_cas03",
	"arug_cas04",
	"arug_cas05",
	"aru_gld",
	"bat_room",
	"bat_a01",
	"bat_a02",
	"bat_b01",
	"bat_b02",
	"que_qsch01",
	"que_qsch02",
	"que_qsch03",
	"que_qsch04",
	"que_qsch05",
	"que_qaru01",
	"que_qaru02",
	"que_qaru03",
	"que_qaru04",
	"que_qaru05",
	"1@cata",
	"2@cata",
	"e_tower",
	"1@tower",
	"2@tower",
	"3@tower",
	"4@tower",
	"5@tower",
	"6@tower",
	"mid_camp",
	"mid_campin",
	"man_fild01",
	"man_fild03",
	"spl_fild02",
	"spl_fild03",
	"moc_fild22b",
	"que_dan01",
	"que_dan02",
	"schg_que01",
	"schg_dun01",
	"arug_que01",
	"arug_dun01",
	"1@orcs",
	"2@orcs",
	"1@nyd",
	"2@nyd",
	"nyd_dun01",
	"nyd_dun02",
	"manuk",
	"man_fild02",
	"man_in01",
	"splendide",
	"spl_fild01",
	"spl_in01",
	"spl_in02",
	"bat_c01",
	"bat_c02",
	"bat_c03",
	"moc_para01",
	"job3_arch01",
	"job3_arch02",
	"job3_arch03",
	"job3_guil01",
	"job3_guil02",
	"job3_guil03",
	"job3_rang01",
	"job3_rang02",
	"job3_rune01",
	"job3_rune02",
	"job3_rune03",
	"job3_war01",
	"job3_war02",
	"jupe_core2",
	"brasilis",
	"bra_in01",
	"bra_fild01",
	"bra_dun01",
	"bra_dun02",
	"dicastes01",
	"dicastes02",
	"dic_in01",
	"dic_fild01",
	"dic_fild02",
	"dic_dun01",
	"dic_dun02",
	"job3_gen01",
	"s_atelier",
	"job3_sha01",
	//"evt_zombie",
	//"evt_coke",
	//"ac_sl_area",
	//"ac_cl_hall",
	//"ac_cl_room",
	//"jp_s_dun11",
	"mora",
	"bif_fild01",
	"bif_fild02",
	"1@mist",
	"dewata",
	"dew_in01",
	"dew_fild01",
	"dew_dun01",
	"dew_dun02",
	"que_house_s",
	"malangdo",
	"mal_in01",
	"mal_in02",
	"mal_dun01",
	"1@pump",
	"2@pump",
	"1@cash",
	"iz_dun05",
	"evt_mobroom",
	"alde_tt03",
	"dic_dun03",
	//"mjolnir_04_1",
	//"evt_swar_b",
	//"evt_swar_r",
	//"evt_swar_s",
	//"evt_swar_t",
	"1@lhz",
	"lhz_dun04",
	"que_lhz",
	"gld_dun01_2",
	"gld_dun02_2",
	"gld_dun03_2",
	"gld_dun04_2",
	"gld2_ald",
	"gld2_gef",
	"gld2_pay",
	"gld2_prt",
	"malaya",
	"ma_fild01",
	"ma_fild02",
	"ma_scene01",
	"ma_in01",
	"ma_dun01",
	"1@ma_h",
	"1@ma_c",
	"1@ma_b",
	"ma_zif01",
	"ma_zif02",
	"ma_zif03",
	"ma_zif04",
	"ma_zif05",
	"ma_zif06",
	"ma_zif07",
	"ma_zif08",
	"ma_zif09",
	"job_ko",
	"eclage",
	"ecl_fild01",
	"ecl_in01",
	"ecl_in02",
	"ecl_in03",
	"ecl_in04",
	"1@ecl",
	"ecl_tdun01",
	"ecl_tdun02",
	"ecl_tdun03",
	"ecl_tdun04",
	"ecl_hub01",
	"que_avan01",
	"moc_prydn1",
	"moc_prydn2",
	"iz_int",
	"iz_int01",
	"iz_int02",
	"iz_int03",
	"iz_int04",
	"iz_ac01",
	"iz_ac02",
	"iz_ng01",
	"treasure_n1",
	"treasure_n2",
	"iz_ac01_d",
	"iz_ac02_d",
	"iz_ac01_c",
	"iz_ac02_c",
	"iz_ac01_b",
	"iz_ac02_b",
	"iz_ac01_a",
	"iz_ac02_a",
	"izlude_d",
	"izlude_c",
	"izlude_b",
	"izlude_a",
	"prt_fild08d",
	"prt_fild08c",
	"prt_fild08b",
	"prt_fild08a",
	"te_prt_gld",
	"te_prtcas01",
	"te_prtcas02",
	"te_prtcas03",
	"te_prtcas04",
	"te_prtcas05",
	"teg_dun01",
	"teg_dun02",
	"te_alde_gld",
	"te_aldecas1",
	"te_aldecas2",
	"te_aldecas3",
	"te_aldecas4",
	"te_aldecas5",
	"1@gl_k",
	"2@gl_k",
	"gl_cas02_",
	"gl_chyard_",
	"silk_lair",
	"evt_bomb",
	"1@def01",
	"1@def02",
	"1@def03",
	"1@face",
	"1@sara",
	"dali",
	"dali02",
	"1@tnm1",
	"1@tnm2",
	"1@tnm3",
	"1@ge_st",
	"1@gef",
	"1@gef_in",
	"1@spa",
	"moro_vol",
	"moro_cav",
	"1@dth1",
	"1@dth2",
	"1@dth3",
	"1@rev",
	"1@xm_d",
	"1@eom",
	"1@jtb",
	"c_tower2_",
	"c_tower3_",
	//"rwc01",
	//"rwc02",
	//"rwc03",
	//"2009rwc_f01",
	//"2009rwc_01",
	//"2009rwc_02",
	//"2009rwc_03",
	//"2009rwc_04",
	//"2008rwc_04",
	//"prontera_x",
	//"alberta_x",
	//"aldebaran_x",
	//"geffen_x",
	//"izlude_x",
	//"prt_church_x",
	//"prontera_s",
	//"pay_arche_s",
	//"xmas_old",
	//"ordeal_a00",
	//"ordeal_a02",
	//"fay_vilg00",
	//"fay_vilg01",
	//"gef_vilg00",
	//"gef_vilg01",
	//"moc_dugn01",
	//"moc_dugn02",
	//"moc_fild01",
	//"moc_fild02",
	//"moc_fild03",
	//"moc_fild04",
	//"moc_intr00",
	//"moc_intr01",
	//"moc_intr02",
	//"moc_intr04",
	//"moc_vilg00",
	//"moc_vilg01",
	//"moc_vilg02",
	//"probemap",
	//"probemap02",
	//"prt_cstl01",
	//"prt_dugn00",
	//"prt_dugn01",
	//"prt_fild00",
	//"prt_fild01",
	//"prt_fild03",
	//"prt_fild04",
	//"prt_fild05",
	//"prt_intr01",
	//"prt_intr01_a",
	//"prt_intr02",
	//"prt_vilg00",
	//"prt_vilg01",
	//"prt_vilg02",
	//"tank_test",
	//"tank_test2",
	//"test",

	/** Mapas Personalizados **/
	"custom_map"
};

char *grf_list_file;
char *map_cache_file;
int rebuild = 0;

FILE *map_cache_fp;

unsigned long file_size;

// Used internally, this structure contains the physical map cells
struct map_data {
	int16 xs;
	int16 ys;
	unsigned char *cells;
};

// This is the main header found at the very beginning of the file
struct main_header {
	uint32 file_size;
	uint16 map_count;
} header;

// This is the header appended before every compressed map cells info
struct map_info {
	char name[MAP_NAME_LENGTH];
	int16 xs;
	int16 ys;
	int32 len;
};

 /*************************************
 * Big-endian compatibility functions *
 * Moved to utils.h                   *
 *************************************/

// Reads a map from GRF's GAT and RSW files
int read_map(char *name, struct map_data *m)
{
	char filename[256];
	unsigned char *gat, *rsw;
	int water_height;
	size_t xy, off, num_cells;

	// Open map GAT
	sprintf(filename,"data\\%s.gat", name);
	gat = (unsigned char *)grfio_read(filename);
	if (gat == NULL)
		return 0;

	// Open map RSW
	sprintf(filename,"data\\%s.rsw", name);
	rsw = (unsigned char *)grfio_read(filename);

	// Read water height
	if (rsw) {
		water_height = (int)GetFloat(rsw+166);
		aFree(rsw);
	} else
		water_height = NO_WATER;

	// Read map size and allocate needed memory
	m->xs = (int16)GetULong(gat+6);
	m->ys = (int16)GetULong(gat+10);
	if (m->xs <= 0 || m->ys <= 0) {
		aFree(gat);
		return 0;
	}
	num_cells = (size_t)m->xs*(size_t)m->ys;
	m->cells = (unsigned char *)aMalloc(num_cells);

	// Set cell properties
	off = 14;
	for (xy = 0; xy < num_cells; xy++) {
		// Height of the bottom-left corner
		float height = GetFloat(gat + off);
		// Type of cell
		uint32 type = GetULong(gat + off + 16);
		off += 20;

		if (type == 0 && water_height != NO_WATER && height > water_height)
			type = 3; // Cell is 0 (walkable) but under water level, set to 3 (walkable water)

		m->cells[xy] = (unsigned char)type;
	}

	aFree(gat);

	return 1;
}

/**
 * Adds a map to the cache.
 *
 * @param name The map name.
 * @param m    Map data to cache.
 * @retval true if the map was successfully added to the cache.
 */
bool cache_map(char *name, struct map_data *m)
{
	struct map_info info;
	unsigned long len;
	unsigned char *write_buf;

	// Create an output buffer twice as big as the uncompressed map... this way we're sure it fits
	len = (unsigned long)m->xs*(unsigned long)m->ys*2;
	write_buf = (unsigned char *)aMalloc(len);
	// Compress the cells and get the compressed length
	encode_zip(write_buf, &len, m->cells, m->xs*m->ys);

	// Fill the map header
	safestrncpy(info.name, name, MAP_NAME_LENGTH);
	if (strlen(name) > MAP_NAME_LENGTH) // It does not hurt to warn that there are maps with name longer than allowed.
		ShowWarning("Nome do mapa '%s' (tam %"PRIuS") muito extenso. Truncando '%s' (tam %d).\n",
		            name, strlen(name), info.name, MAP_NAME_LENGTH);
	info.xs = MakeShortLE(m->xs);
	info.ys = MakeShortLE(m->ys);
	info.len = MakeLongLE((uint32)len);

	// Append map header then compressed cells at the end of the file
	if (fseek(map_cache_fp, header.file_size, SEEK_SET) != 0) {
		aFree(write_buf);
		aFree(m->cells);
		return false;
	}
	fwrite(&info, sizeof(struct map_info), 1, map_cache_fp);
	fwrite(write_buf, 1, len, map_cache_fp);
	header.file_size += sizeof(struct map_info) + len;
	header.map_count++;

	aFree(write_buf);
	aFree(m->cells);

	return true;
}

/**
 * Checks whether a map is already is the cache.
 *
 * @param name The map name.
 * @retval true if the map is already cached.
 */
bool find_map(char *name)
{
	int i;
	struct map_info info;

	if (fseek(map_cache_fp, sizeof(struct main_header), SEEK_SET) != 0)
		return false;

	for (i = 0; i < header.map_count; i++) {
		if (fread(&info, sizeof(info), 1, map_cache_fp) != 1)
			printf("An error as occured in fread while reading map_cache\n");
		if (strcmp(name, info.name) == 0) // Map found
			return true;
		// Map not found, jump to the beginning of the next map info header
		if (fseek(map_cache_fp, GetLong((unsigned char *)&(info.len)), SEEK_CUR) != 0)
			return false;
	}

	return false;
}

// Cuts the extension from a map name
char *remove_extension(char *mapname)
{
	char *ptr, *ptr2;
	ptr = strchr(mapname, '.');
	if (ptr) { //Check and remove extension.
		while (ptr[1] && (ptr2 = strchr(ptr+1, '.')) != NULL)
			ptr = ptr2; //Skip to the last dot.
		if (strcmp(ptr,".gat") == 0)
			*ptr = '\0'; //Remove extension.
	}
	return mapname;
}

/**
 * --grf-list handler
 *
 * Overrides the default grf list filename.
 * @see cmdline->exec
 */
static CMDLINEARG(grflist)
{
	aFree(grf_list_file);
	grf_list_file = aStrdup(params);
	return true;
}

/**
 * --map-cache handler
 *
 * Overrides the default map cache filename.
 * @see cmdline->exec
 */
static CMDLINEARG(mapcache)
{
	aFree(map_cache_file);
	map_cache_file = aStrdup(params);
	return true;
}

/**
 * --rebuild handler
 *
 * Forces a rebuild of the mapcache, rather than only adding missing maps.
 * @see cmdline->exec
 */
static CMDLINEARG(rebuild)
{
	rebuild = 1;
	return true;
}

/**
 * Defines the local command line arguments
 */
void cmdline_args_init_local(void)
{
	CMDLINEARG_DEF2(grf-list, grflist, "Alternativa lista de grf", CMDLINE_OPT_NORMAL|CMDLINE_OPT_PARAM);
	CMDLINEARG_DEF2(map-cache, mapcache, "Alternativo arquivo de cache", CMDLINE_OPT_NORMAL|CMDLINE_OPT_PARAM);
	CMDLINEARG_DEF2(rebuild, rebuild, "For�a uma reconstru��o do cache do mapa, em vez de apenas adicionar mapas desaparecidos", CMDLINE_OPT_NORMAL);

}

int do_init(int argc, char** argv)
{
	struct map_data map;
	char name[MAP_NAME_LENGTH_EXT];
	int i;

	grf_list_file = aStrdup("conf/grf-files.txt");
	map_cache_file = aStrdup("db/"DBPATH"map_cache.dat");

	cmdline->exec(argc, argv, CMDLINE_OPT_PREINIT);
	cmdline->exec(argc, argv, CMDLINE_OPT_NORMAL);

	ShowStatus("inicializando grfio com %s\n", grf_list_file);
	grfio_init(grf_list_file);

	// Attempt to open the map cache file and force rebuild if not found
	ShowStatus("Abrindo mapcache: %s\n", map_cache_file);
	if(!rebuild) {
		map_cache_fp = fopen(map_cache_file, "rb");
		if(map_cache_fp == NULL) {
			ShowNotice("Existente mapcache nao encontrado, forcando o modo rebuild\n");
			rebuild = 1;
		} else
			fclose(map_cache_fp);
	}
	if(rebuild)
		map_cache_fp = fopen(map_cache_file, "w+b");
	else
		map_cache_fp = fopen(map_cache_file, "r+b");
	if(map_cache_fp == NULL) {
		ShowError("Falha ao abrir o mapcache %s\n", map_cache_file);
		exit(EXIT_FAILURE);
	}

	// Initialize the main header
	if(rebuild) {
		header.file_size = sizeof(struct main_header);
		header.map_count = 0;
	} else {
		if(fread(&header, sizeof(struct main_header), 1, map_cache_fp) != 1){ printf("Ocorreu um erro em map_cache_fp \n"); }
		header.file_size = GetULong((unsigned char *)&(header.file_size));
		header.map_count = GetUShort((unsigned char *)&(header.map_count));
	}

	// Read and process the map list
	for (i = 0; i < (sizeof(map_list) / sizeof(map_list[0])); i++) {
		if (map_list[i] == NULL)
			continue;

		strncpy(name, map_list[i], sizeof(name));
		name[MAP_NAME_LENGTH_EXT-1] = '\0';
		remove_extension(name);

		if (find_map(name)) {
			ShowInfo("Mapa '"CL_WHITE"%s"CL_RESET"' ja esta em cache.\n", name);
		} else if(!read_map(name, &map)) {
			ShowError("Mapa '"CL_WHITE"%s"CL_RESET"' nao encontrado!\n", name);
		} else if (!cache_map(name, &map)) {
			ShowError("Mapa cache '"CL_WHITE"%s"CL_RESET"' falhou (erro de gravacao).\n", name);
		} else {
			ShowInfo("Mapa '"CL_WHITE"%s"CL_RESET"' carregado com sucesso.\n", name);
		}
	}

	// Write the main header and close the map cache
	ShowStatus("Fechando o mapcache: %s\n", map_cache_file);
	fseek(map_cache_fp, 0, SEEK_SET);
	fwrite(&header, sizeof(struct main_header), 1, map_cache_fp);
	fclose(map_cache_fp);

	ShowStatus("Finalizando grfio\n");
	grfio_final();

	ShowInfo("%d mapas em cache\n", header.map_count);

	aFree(grf_list_file);
	aFree(map_cache_file);
	return 0;
}

int do_final(void)
{
	return EXIT_SUCCESS;
}
