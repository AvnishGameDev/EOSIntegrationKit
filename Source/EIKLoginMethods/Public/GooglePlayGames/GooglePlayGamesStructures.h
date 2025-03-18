#pragma once

#include "CoreMinimal.h"
#include "Json.h"
#include "GooglePlayGamesStructures.generated.h"

USTRUCT(BlueprintType)
struct FGPGS_Friend
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	FString PlayerID;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	bool bHasHiResImage;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	bool bHasIconImage;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	FString HiResImageURL;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	FString IconImageURL;
	
	// Constructor
	FGPGS_Friend()
		: DisplayName(TEXT(""))
		, PlayerID(TEXT(""))
		, bHasHiResImage(false)
		, bHasIconImage(false)
		, HiResImageURL(TEXT(""))
		, IconImageURL(TEXT(""))
	{
	}

	static FGPGS_Friend ParseFromJson(const TSharedPtr<FJsonObject>& JsonObject)
	{
		FGPGS_Friend Friend;
		if (JsonObject.IsValid())
		{
			// Read all fields from the JSON object
			JsonObject->TryGetStringField("displayName", Friend.DisplayName);
			JsonObject->TryGetStringField("playerId", Friend.PlayerID);
			JsonObject->TryGetBoolField("hasHiResImage", Friend.bHasHiResImage);
			JsonObject->TryGetBoolField("hasIconImage", Friend.bHasIconImage);
			JsonObject->TryGetStringField("hiResImageUrl", Friend.HiResImageURL);
			JsonObject->TryGetStringField("iconImageUrl", Friend.IconImageURL);
		}
		return Friend;
	}

	static TArray<FGPGS_Friend> ParseFriendArrayFromJson(const FString& JsonString)
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		TArray<FGPGS_Friend> Friends;

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			// Get the array of friends
			const TArray<TSharedPtr<FJsonValue>>* FriendsJsonArray;
			if (JsonObject->TryGetArrayField("friends", FriendsJsonArray))
			{
				// Process each friend in the array
				for (const TSharedPtr<FJsonValue>& Value : *FriendsJsonArray)
				{
					TSharedPtr<FJsonObject> FriendObject = Value->AsObject();
					if (FriendObject.IsValid())
					{
						// Create a new friend, parse it, and add it to the array
						Friends.Add(FGPGS_Friend::ParseFromJson(FriendObject));
					}
				}
			}
		}

		return Friends;
	}
};

USTRUCT(BlueprintType)
struct FGPGS_Event
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	FString Description;
	
	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	FString EventID;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	int64 Value;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	bool bIsVisible;

	// Constructor
	FGPGS_Event()
		: Name(TEXT(""))
		, Description(TEXT(""))
		, EventID(TEXT(""))
		, Value(0)
		, bIsVisible(false)
	{
	}

	static FGPGS_Event ParseFromJson(const FString& JsonString)
	{
		FGPGS_Event Event;
		
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			if (JsonObject.IsValid())
			{
				// Read all fields from the JSON object
				JsonObject->TryGetStringField("name", Event.Name);
				JsonObject->TryGetStringField("description", Event.Description);
				JsonObject->TryGetStringField("eventId", Event.EventID);
				JsonObject->TryGetNumberField("value", Event.Value);
				JsonObject->TryGetBoolField("isVisible", Event.bIsVisible);
			}
		}
		return Event;
	}
};

USTRUCT(BlueprintType)
struct FGPGS_PlayerStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	float AverageSessionLength;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	int32 DaysSinceLastPlayed;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	int32 NumberOfPurchases;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	int32 NumberOfSessions;
	
	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	float SessionPercentile;

	UPROPERTY(BlueprintReadOnly, Category = "Google Play Games")
	float SpendPercentile;

	FGPGS_PlayerStats()
		: AverageSessionLength(0)
		, DaysSinceLastPlayed(0)
		, NumberOfPurchases(0)
		, NumberOfSessions(0)
		, SessionPercentile(0)
		, SpendPercentile(0)
	{
	}

	static FGPGS_PlayerStats ParseFromJson(const FString& JsonString)
	{
		FGPGS_PlayerStats PlayerStats;
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			if (JsonObject.IsValid())
			{
				// Read all fields from the JSON object
				JsonObject->TryGetNumberField("averageSessionLength", PlayerStats.AverageSessionLength);
				JsonObject->TryGetNumberField("daysSinceLastPlayed", PlayerStats.DaysSinceLastPlayed);
				JsonObject->TryGetNumberField("numberOfPurchases", PlayerStats.NumberOfPurchases);
				JsonObject->TryGetNumberField("numberOfSessions", PlayerStats.NumberOfSessions);
				JsonObject->TryGetNumberField("sessionPercentile", PlayerStats.SessionPercentile);
				JsonObject->TryGetNumberField("spendPercentile", PlayerStats.SpendPercentile);
			}
		}
		return PlayerStats;
	}
	
};
