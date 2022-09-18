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
        
        // look for the character in the MorseCodeCharacters array
        for (int32 j = 0; j < MorseCodeCharacters.Num(); j++)
        {
            // if the current character is found in the array
            if (CurrentChar == MorseCodeCharacters[j].Character)
            {
                // add the morse code equivalent of the character to the MorseCodeString
                MorseCodeString += MorseCodeCharacters[j].Code + "\n";

                // break out of the loop
                break;
            }

            // If the current character is a space, add a space to the morse code string
            if (CurrentChar == " ")
            {
                MorseCodeString += " ";
            }

             //if the current character is not found in the array
            else if (j == MorseCodeCharacters.Num() - 1)
            {
                // add "Character Not Found" to the MorseCodeString
                MorseCodeString += "Character Not Found";
            }
            
        }

    }

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

            //wait for the dot delay time
            GetWorldTimerManager().SetTimer(DotDelayTimer, this, &AMorseCodePawn::FlashLightOff, DotDelayTime, false, 0);
            PointLight->SetLightColor(FLinearColor::Red);

            UE_LOG(LogTemp, Warning, TEXT("is dot"));
        }


        //if the current character is a dash
        else if (CurrentChar == "-")
        {
            //turn the light on right away
            FlashLightOn();

            //wait for the dash delay time
            GetWorldTimerManager().SetTimer(DashDelayTimer, this, &AMorseCodePawn::FlashLightOff, DashDelayTime, false, 0);
            PointLight->SetLightColor(FLinearColor::Blue);


            UE_LOG(LogTemp, Warning, TEXT("is dash"));
        }

        //if the long pause if character is a space
        else if (CurrentChar == " ")
        {

                //turn the light off
                FlashLightOff();

                //wait for the space delay time
                GetWorldTimerManager().SetTimer(LongPauseTimer, this, &AMorseCodePawn::FlashLightOff, LongPause, false, 0);

                UE_LOG(LogTemp, Warning, TEXT("long Pause"));

        }

        else if (CurrentChar == "Character Not Found")
        {
            FlashLightOff();
        }
    }

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