//Vladyslav Rudenko
#pragma once

#include "windows.h"
#include "GameFramework/Pawn.h"
#include "Templates/UnrealTemplate.h"
#include "Components/InputComponent.h"
#include "Components/PointLightComponent.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "CoreMinimal.h"
#include "MorseCodePawn.generated.h"

USTRUCT(BlueprintType)
struct FMorseCodeCharacter
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code")
		FString Character;
	//char MorseChar = (char)Character[0];

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code")
		FString Code;
};

UCLASS(BlueprintType)
class MORSECODE_API AMorseCodePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMorseCodePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Morse Light")
		class UPointLightComponent* PointLight;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Morse Text")
		class UTextRenderComponent* TextRenderer;


	//Current Morse Character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse String")
		FString CurrentChar;
	//char MorseChar = (char)CurrentChar[0];

	//a string to store a user input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse String")
		FString InputString;	

	//a string to store Morse code version of the input string
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse String")
		FString MorseCodeString;

	//Function converting user input to Morse code
	UFUNCTION(BlueprintCallable, Category = "Input Conversion")
		void ConvertInputToMorseCode();

	//Map of MorseCodeCharacters
	//char is not a recognized type for UPROPERTY
	UPROPERTY(EditFixedSize, BlueprintReadOnly, Category = "Morse Code Translation")
		TMap<FString, FString> MorseCodeCharacters = {
		  {"A", ".-"},
		  {"B", "-..."},
		  {"C", "-.-."},
		  {"D", "-.."},
		  {"E", "."},
		  {"F", "..-."},
		  {"G", "--."},
		  {"H", "...."},
		  {"I", ".."},
		  {"J", ".---"},
		  {"K", "-.-"},
		  {"L", ".-.."},
		  {"M", "--"},
		  {"N", "-."},
		  {"O", "---"},
		  {"P", ".--."},
		  {"Q", "--.-"},
		  {"R", ".-."},
		  {"S", "..."},
		  {"T", "-"},
		  {"U", "..-"},
		  {"V", "...-"},
		  {"W", ".--"},
		  {"X", "-..-"},
		  {"Y", "-.--"},
		  {"Z", "--.."},
		  {"0", "-----"},
		  {"1", ".----"},
		  {"2", "..---"},
		  {"3", "...--"},
		  {"4", "....-"},
		  {"5", "....."},
		  {"6", "-...."},
		  {"7", "--..."},
		  {"8", "---.."},
		  {"9", "----."}
	};


	//the maximum intensity of the point light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Light")
		float MaxIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Light")
	bool bFlashLightOn = true;

	//function clears strings
	UFUNCTION(BlueprintCallable, Category = "Input Conversion")
		void ClearInputText();

	UFUNCTION(BlueprintCallable, Category = "Morse Light")
		void FlashLightOn();

	UFUNCTION(BlueprintCallable, Category = "Morse Light")
		void FlashLightOff();

	UFUNCTION(BlueprintCallable, Category = "Morse Code Play")
		void PlayMorseCode();


	//Short signal for dot 0.3 s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code Play")
		FTimerHandle DotDelayTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code Play")
		float DotDelayTime = 0.2f;


	//Long signal for dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code Play")
		FTimerHandle DashDelayTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code Play")
		float DashDelayTime = 0.7f;


	//Long pause between words 1.5 second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code Play")
		FTimerHandle LongPauseTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Morse Code Play")
		float LongPause = 1.0f;
};