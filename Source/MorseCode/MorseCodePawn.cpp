// Vladyslav Rudenko

#include "MorseCodePawn.h"

// Sets default values
AMorseCodePawn::AMorseCodePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComp"));

    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Morse Light"));

    TextRenderer->SetupAttachment(RootComponent);
    PointLight->SetupAttachment(RootComponent);

    MaxIntensity = 5000;
}

// Called when the game starts or when spawned
void AMorseCodePawn::BeginPlay()
{
	Super::BeginPlay();

    FlashLightOff();
    PointLight->SetLightColor(FLinearColor::Red);

}

// Called every frame
void AMorseCodePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMorseCodePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//This function converting user input to a morse code
//loops through each character in the input string, converts it to upper case, and then looks for it in the MorseCodeCharacters array
void AMorseCodePawn::ConvertInputToMorseCode()
{
    // Loop through each character of the input string
    for (int32 i = 0; i < InputString.Len(); i++)
    {
        // convert the current character to upper case
        CurrentChar = InputString.Mid(i, 1).ToUpper();

        // look for the character in the MorseCodeCharacters TMap
        FString* MorseCode = MorseCodeCharacters.Find(CurrentChar);
        if (MorseCode != nullptr)
        {
            // if the character is found, add the corresponding Morse code to the MorseCodeString
            MorseCodeString += *MorseCode /*+ "\n"*/;
        }
        else
        {
            // if the character is not found, add "Character Not Found" to the MorseCodeString
            MorseCodeString += "Character Not Found";
        }
    }

    // Set the text of the TextRender component to the generated mor


    // Set the text of the TextRender component to the generated morse code string
    TextRenderer->SetText(FText::FromString(MorseCodeString));

    UE_LOG(LogTemp, Warning, TEXT("InputString: %s"), *InputString);
    UE_LOG(LogTemp, Warning, TEXT("CurrentChar: %s"), *CurrentChar);
    UE_LOG(LogTemp, Warning, TEXT("ConvertInputToMorseCode: %s"), *MorseCodeString);

}

//This function playing Morse code using Point Light Component
//switch statement only supports int, char, enum types.I am passing FString.I need to use if, else if in my case.
void AMorseCodePawn::PlayMorseCode()
{
    //go through each character of the morse code string
   for (int i = 0; i < MorseCodeString.Len(); i++)
        {
            //get the current character
            CurrentChar = MorseCodeString.Mid(i, 1);

            //if the current character is a dot
            if (CurrentChar == ".")
            {
                //turn the light on right away
                FlashLightOn();

                //set a timer delegate function to turn the light off after the dot delay time
                FTimerDelegate DotTimerDelegate = FTimerDelegate::CreateUObject(this, &AMorseCodePawn::FlashLightOff);
                GetWorldTimerManager().SetTimer(DotDelayTimer, DotTimerDelegate, DotDelayTime, false, 0.2f);
                PointLight->SetLightColor(FLinearColor::Red);
            }

            //if the current character is a dash
            else if (CurrentChar == "-")
            {
                //turn the light on right away
                FlashLightOn();

                //set a timer delegate function to turn the light off after the dash delay time
                FTimerDelegate DashTimerDelegate = FTimerDelegate::CreateUObject(this, &AMorseCodePawn::FlashLightOff);
                GetWorldTimerManager().SetTimer(DashDelayTimer, DashTimerDelegate, DashDelayTime, false, 0.7f);
                PointLight->SetLightColor(FLinearColor::Blue);
            }

            //if the current character is a space
            else if (CurrentChar == " ")
            {
                //turn the light off
                FlashLightOff();

                //set a timer delegate function to turn the light off after the space delay time
                FTimerDelegate SpaceTimerDelegate = FTimerDelegate::CreateUObject(this, &AMorseCodePawn::FlashLightOff);
                GetWorldTimerManager().SetTimer(LongPauseTimer, SpaceTimerDelegate, LongPause, false, 1.0f);
            }

            //if the current character is "Character Not Found"
            else if (CurrentChar == "Character Not Found")
            {
                //turn the light off
                FlashLightOff();
            }
        }
   //add a delay after the loop has completed
   FTimerDelegate SpaceTimerDelegate = FTimerDelegate::CreateUObject(this, &AMorseCodePawn::FlashLightOff);
   GetWorldTimerManager().SetTimer(LongPauseTimer, SpaceTimerDelegate, LongPause, false, 1.0f);

    UE_LOG(LogTemp, Warning, TEXT("The End of the PlayMorse Code, CurrentChar: %s"), *CurrentChar);
}

//It clears the text from the text renderer and sets the string variables to empty strings.
void AMorseCodePawn::ClearInputText()
{

    //set the InputString variable to an empty string
    InputString = "";

    //set the MorseCodeString variable to an empty string
    MorseCodeString = "";

    //set the text of the TextRender component 
    TextRenderer->SetText(FText::FromString(MorseCodeString));
}

//function to turn on the Point Light Component
void AMorseCodePawn::FlashLightOn()
{
      bFlashLightOn = true;
      PointLight->SetIntensity(5000.0);
}

//function to turn off the Point Light Component
void AMorseCodePawn::FlashLightOff()
{
      bFlashLightOn = false;
      PointLight->SetIntensity(0);
}