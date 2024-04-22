// Liuxijun


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	// 返回唯一的游戏标签管理器
	// UGameplayTagsManager::Get();
	// 添加本机游戏标签
	static UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	/**
	 * Primary Attributes
	 */
	GameplayTags.Attribute_Primary_Strength = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage")
		);
	GameplayTags.Attribute_Primary_Intelligence = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage")
		);
	GameplayTags.Attribute_Primary_Resilience = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Increases Armor and Armor Penetration")
		);
	GameplayTags.Attribute_Primary_Vigor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases Health")
		);


	/**
	* Secondary Attributes
	*/ 
	GameplayTags.Attribute_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance")
		);
	GameplayTags.Attribute_Secondary_ArmorPenetration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignores percentage of enemy Armor, increase Critical Hit Chance")
		);
	GameplayTags.Attribute_Secondary_BlockChance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to cut incoming damage in half")
		);
	GameplayTags.Attribute_Secondary_CriticalHitChance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance to double damage plus critical hit bonus")
		);
	GameplayTags.Attribute_Secondary_CriticalHitDamage = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage added when a critical hit is scored")
		);
	GameplayTags.Attribute_Secondary_CriticalHitResistance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Reduces critical hit chance of attacking enemies")
		);
	GameplayTags.Attribute_Secondary_HealthRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of Health regenerated every 1 second")
		);
	GameplayTags.Attribute_Secondary_ManaRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of Mana regenerated every 1 second")
		);
	GameplayTags.Attribute_Secondary_MaxHealth = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of Health obtainable")
		);
	GameplayTags.Attribute_Secondary_MaxMana = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum amount of Mana obtainable")
		);
	
}
