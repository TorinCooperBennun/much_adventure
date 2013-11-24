/* Copyright 2013 Torin Cooper-Bennun
 *
 * This file is part of wagnventures.
 * 
 * wagnventures is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * wagnventures is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with wagnventures.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef ITEM_TYPES_H
#define ITEM_TYPES_H


enum item_type
{
	WEAPON,
	FOOD,
	ARMOUR,
	POTION,
	TREASURE,
	MONEY,
        NULL_TYPE,
};


enum weapon_type
{
	LEMON,
	MAGICAL_RAINBOW_UNICORN_SABER_OF_SATAN,
	MACHETE,
	STICK,
	SCIMITAR,
	SCYTHE,
	GLASS_ROD,
};


enum potion_type
{
	HEALTH,
	HUNGER,
	POISON,
	STRENGTH,
	INVISIBILITY,
	ABSORPTION,
	EXTRA_HEALTH,
};


enum food_type
{
	PUMPKIN_PIE,
	APPLE,
	BANANA,
	UNICORN_BLOOD,
	BEETLEJUICE,
	POTATO_SALAD,
	POPCORN,
	RAW_STEAK,
	COOKED_STEAK,
	RAW_CHICKEN,
	ROAST_CHICKEN,
	FULL_ENGLISH,
	PIZZA,
};


enum money_type
{
	COIN,
	BANKNOTE,
};


enum armour_type
{
	HELMET,
	BREASTPLATE,
	GAUNTLETS,
	BOOTS,
	SHOULDERPADS,
	KNEEPADS,
	GOGGLES,
	EARMUFFS,
};


enum armour_material_type
{
	GOLD,
	COTTON,
	WOOD,
	STEEL,
	IRON,
	GLASS,
	DIAMOND,
	DWARVEN,
};
 

enum treasure_type
{
	CROWN,
	NECKLACE,
	JEWELS,
	BRACELET,
	GEM,
	RING,
	SCROLL,
	BOOK,
};


#endif
