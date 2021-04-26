// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfo_Instance.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


UGameInfo_Instance::UGameInfo_Instance()
{
	//bReplicates = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> MAINMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/MainMenu.MainMenu_C'"));
	if (MAINMENU_WIDGET.Succeeded()) MainMenu_Class = MAINMENU_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> HOSTMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/HostMenu.HostMenu_C'"));
	if (HOSTMENU_WIDGET.Succeeded()) HostMenu_Class = HOSTMENU_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> SERVERMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/ServerMenu.ServerMenu_C'"));
	if (SERVERMENU_WIDGET.Succeeded()) ServerMenu_Class = SERVERMENU_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> OPTIONMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/OptionsMenu.OptionsMenu_C'"));
	if (OPTIONMENU_WIDGET.Succeeded()) OptionMenu_Class = OPTIONMENU_WIDGET.Class;

}

void UGameInfo_Instance::Init()
{
}


void UGameInfo_Instance::Show_MainMenu()
{
	auto PlayerContoller = GetFirstLocalPlayerController();
	if (MainMenu_WB == nullptr) {
		MainMenu_WB = CreateWidget<UUserWidget>(PlayerContoller, MainMenu_Class);
	}
	MainMenu_WB->AddToViewport();
	PlayerContoller->bShowMouseCursor = true;
}

void UGameInfo_Instance::Show_HostMenu()
{
	auto PlayerContoller = GetFirstLocalPlayerController();
	if (HostMenu_WB == nullptr) {
		HostMenu_WB = CreateWidget<UUserWidget>(PlayerContoller, HostMenu_Class);
	}
	HostMenu_WB->AddToViewport();
	PlayerContoller->bShowMouseCursor = true;
}

void UGameInfo_Instance::Show_ServerMenu()
{
	auto PlayerContoller = GetFirstLocalPlayerController();
	ServerMenu_WB = CreateWidget<UUserWidget>(PlayerContoller, ServerMenu_Class);
	ServerMenu_WB->AddToViewport();
	PlayerContoller->bShowMouseCursor = true;
}

void UGameInfo_Instance::Option_Menu()
{
	auto PlayerContoller = GetFirstLocalPlayerController();
	if (OptionMenu_WB == nullptr) {
		OptionMenu_WB = CreateWidget<UUserWidget>(PlayerContoller, OptionMenu_Class);
	}
	OptionMenu_WB->AddToViewport();
	PlayerContoller->bShowMouseCursor = true;
}

void UGameInfo_Instance::Launch_Lobby(int32 Player_Num, FText Server_Name, bool IsLan)
{
	MaxPlayer = Player_Num;
	ServerName = Server_Name;
	if (ShowLoddingScreen.IsBound()) ShowLoddingScreen.Broadcast();
}

void UGameInfo_Instance::Show_LoddingScreen()
{
}

void UGameInfo_Instance::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(UGameInfo_Instance, Owner);
}
