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
