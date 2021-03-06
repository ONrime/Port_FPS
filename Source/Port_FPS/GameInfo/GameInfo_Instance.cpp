// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfo_Instance.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Components/SlateWrapperTypes.h"
#include "OptionMenu_UserWidget.h"


UGameInfo_Instance::UGameInfo_Instance()
{
	//bReplicates = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> MAINMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/MainMenu.MainMenu_C'"));
	if (MAINMENU_WIDGET.Succeeded()) MainMenu_Class = MAINMENU_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> HOSTMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/HostMenu.HostMenu_C'"));
	if (HOSTMENU_WIDGET.Succeeded()) HostMenu_Class = HOSTMENU_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> SERVERMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/ServerMenu.ServerMenu_C'"));
	if (SERVERMENU_WIDGET.Succeeded()) ServerMenu_Class = SERVERMENU_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UOptionMenu_UserWidget> OPTIONMENU_WIDGET(TEXT("WidgetBlueprint'/Game/UI/MainMenu/OptionsMenu.OptionsMenu_C'"));
	if (OPTIONMENU_WIDGET.Succeeded()) OptionMenu_Class = OPTIONMENU_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> LOADINGSCREEN_WIDGET(TEXT("WidgetBlueprint'/Game/UI/Levels/LoadingScreen.LoadingScreen_C'"));
	if (LOADINGSCREEN_WIDGET.Succeeded()) LodingScreen_Class = LOADINGSCREEN_WIDGET.Class;

}

void UGameInfo_Instance::Init()
{
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get()) {
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			//SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGameInfo_Instance::OnCreateSessionComplete);
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGameInfo_Instance::OnCreateSessionComplete_Lobby);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UGameInfo_Instance::OnJoinSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UGameInfo_Instance::OnFindSessionsComplete);
		}
	}
	SessionSearch.Reset();

	ShowMainMenu.AddUObject(this, &UGameInfo_Instance::Show_MainMenu);
	ShowLodingScreen.AddUObject(this, &UGameInfo_Instance::Show_LodingScreen);
	//GetEngine()->OnNetworkFailure().AddUObject(this, &UGameInfo_Instance::HandleNetworkError);
}

void UGameInfo_Instance::OnCreateSessionComplete(FName Server_Name, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete: Succeeded %d"), Succeeded);
	if (Succeeded) {
		GetWorld()->ServerTravel("/Game/Maps/LobyMap.LobyMap?listen");
	}

}

void UGameInfo_Instance::OnCreateSessionComplete_Lobby(FName Server_Name, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("Lobby: OnCreateSessionComplete Succeeded %d"), Succeeded);
	if (Succeeded) {
		//GetWorld()->ServerTravel("/Game/Maps/LobyMap.LobyMap?listen");
		UGameplayStatics::OpenLevel(GetWorld(), LobbyName, true, "listen");
	}
	else {  // ?????? ???????? ???????? ??

	}
}

void UGameInfo_Instance::OnJoinSessionComplete(FName Server_Name, EOnJoinSessionCompleteResult::Type type)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("OnJoinSessionComplete"));
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete: Succeeded %d"), type);
	if (type == EOnJoinSessionCompleteResult::Success) {
		UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete: Succeeded"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete: Failed"));
	}
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(Server_Name, JoinAddress);
		PC->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
	}
}

void UGameInfo_Instance::OnFindSessionsComplete(bool Succeeded)
{
	
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete: Succeeded %d"), Succeeded);
	if (Succeeded) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("OnFindSessionsSucceeded"));
		SessionsNum = SessionSearch->SearchResults.Num();
		IsFindServer = true;
		//Join_Server();
		FindSessionSucceeded.Broadcast();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("OnFindSessionsFailed"));
		IsFindServer = false;
		FindSessionFaild.Broadcast();
	}

}

/*void UGameInfo_Instance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	//HandleNetworkError()
}*/

void UGameInfo_Instance::HandleNetworkError(ENetworkFailure::Type FailureType, bool bIsServer)
{
	if (!bIsServer) {
		UE_LOG(LogTemp, Warning, TEXT("NetError: %s"), *NetErrorToString(FailureType));
	}
}

void UGameInfo_Instance::HandleTravelError(ETravelFailure::Type FailureType)
{
	UE_LOG(LogTemp, Warning, TEXT("TravelError: %s"), *TravelErrorToString(FailureType));
}

void UGameInfo_Instance::CreateServer(int32 Player_Num, FName Server_Name, bool Lan)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("CreateServer"));
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = false;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;

	SessionInterface->CreateSession(Player_Num, "test", SessionSettings);
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

void UGameInfo_Instance::Show_OptionMenu()
{
	auto PlayerContoller = GetFirstLocalPlayerController();
	if (OptionMenu_WB == nullptr) {
		OptionMenu_WB = CreateWidget<UOptionMenu_UserWidget>(PlayerContoller, OptionMenu_Class);
	}
	OptionMenu_WB->AddToViewport();
	PlayerContoller->bShowMouseCursor = true;

	if (!IsCreateSaveFile) {
		OptionMenu_WB->WelcomeMessageVis = ESlateVisibility::Visible;
	}
	else {
		OptionMenu_WB->WelcomeMessageVis = ESlateVisibility::Hidden;
	}
}

void UGameInfo_Instance::Launch_Lobby(int32 Player_Num, FName Server_Name, bool Lan)
{
	MaxPlayer = Player_Num;
	ServerName = Server_Name;
	if (ShowLodingScreen.IsBound()) {
		ShowLodingScreen.Broadcast();
		CreateServer(Player_Num, Server_Name, Lan);
	}
}

void UGameInfo_Instance::Join_Server()
{
	/*if (ShowLodingScreen.IsBound()) {
		ShowLodingScreen.Broadcast();
		// Sessions, SessionInterface???? ???? JoinSession ???????? 
		
	}*/
	TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
	UE_LOG(LogTemp, Warning, TEXT("SearchResults Count: %d"), SearchResults.Num());
	if (SearchResults.Num()) {
		//ServerName= SearchResults[0]->
		SessionInterface->JoinSession(0, "test", SearchResults[0]);
	}
}

void UGameInfo_Instance::Find_Server()
{
	/*SessionSearch.Reset();
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false; //lan ????
	SessionSearch->MaxSearchResults = 20;
	SessionSearch->PingBucketSize = 50;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);*/

	//SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());

	// Get the OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		// Get the SessionInterface from our OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->bIsLanQuery = false;
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->PingBucketSize = 50;
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

			TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();

			// Finally call the SessionInterface function. The Delegate gets called once this is finished
			SessionInterface->FindSessions(0, SearchSettingsRef);
		}
	}
	else
	{
		// If something goes wrong, just call the Delegate Function directly with "false".
		OnFindSessionsComplete(false);
	}
		
}

void UGameInfo_Instance::Show_LodingScreen()
{
	auto PlayerContoller = GetFirstLocalPlayerController();
	if (LodingScreen_WB == nullptr) {
		LodingScreen_WB = CreateWidget<UUserWidget>(PlayerContoller, LodingScreen_Class);
	}
	LodingScreen_WB->AddToViewport();
}

void UGameInfo_Instance::Destroy_SessionCaller(APlayerController PC)
{
	// DestroySession() ????????
}

void UGameInfo_Instance::Check_SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerSettingsSave, 0)) {
		Show_MainMenu();
		IsCreateSaveFile = true;
	}
	else {
		Show_OptionMenu();
		auto PlayerContoller = GetFirstLocalPlayerController();
		PlayerContoller->bShowMouseCursor = true;
	}
}

FString UGameInfo_Instance::NetErrorToString(ENetworkFailure::Type FailureType)
{
	return FString();
}

FString UGameInfo_Instance::TravelErrorToString(ETravelFailure::Type FailureType)
{
	return FString();
}

void UGameInfo_Instance::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(UGameInfo_Instance, Owner);
}
