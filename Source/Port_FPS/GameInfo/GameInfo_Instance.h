// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GameInfo_Instance.generated.h"

/**
 * 
 */



UCLASS()
class PORT_FPS_API UGameInfo_Instance : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInfo_Instance();

	DECLARE_EVENT(UGameInfo_Instance, FGameMenu);
	DECLARE_EVENT_ThreeParams(UGameInfo_Instance, FGameLaunch, int32, FName, bool);
	DECLARE_EVENT_OneParam(UGameInfo_Instance, FJoinGame, IOnlineSessionPtr);
	DECLARE_EVENT_OneParam(UGameInfo_Instance, FDestroyGame, class APlyaerController);

protected:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName Server_Name, bool Succeeded);
	virtual void OnCreateSessionComplete_Lobby(FName Server_Name, bool Succeeded);
	virtual void OnJoinSessionComplete(FName Server_Name, EOnJoinSessionCompleteResult::Type type);
	//virtual void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
	virtual void HandleNetworkError(ENetworkFailure::Type FailureType, bool bIsServer); // ��Ʈ��ũ ���� ó�� �� �޼��� ���
	virtual void HandleTravelError(ETravelFailure::Type FailureType); // �̵��� ���� ó�� �� �޼��� ���

	UFUNCTION(BlueprintCallable)
	void CreateServer(int32 Player_Num, FName Server_Name, bool IsLan);

public:
	FGameMenu ShowMainMenu;
	FGameMenu ShowHostMenu;
	FGameMenu ShowServerMenu;
	FGameMenu ShowOptionMenu;
	FGameMenu ShowLodingScreen;
	FGameLaunch LaunchLobby;
	FJoinGame JoinSession;
	FDestroyGame DestroySessionCaller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* MainMenu_WB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* HostMenu_WB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* ServerMenu_WB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UOptionMenu_UserWidget* OptionMenu_WB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* LodingScreen_WB;

	TSubclassOf<class UUserWidget> MainMenu_Class; 
	TSubclassOf<class UUserWidget> HostMenu_Class;
	TSubclassOf<class UUserWidget> ServerMenu_Class;
	TSubclassOf<class UUserWidget> OptionMenu_Class;
	TSubclassOf<class UUserWidget> LodingScreen_Class;

	UFUNCTION(BlueprintCallable, Category = "Event")
	void Show_MainMenu();  // ���� �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Category = "Event")
	void Show_HostMenu();  // ȣ��Ʈ �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Category = "Event")
	void Show_ServerMenu();  // ���� �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Category = "Event")
	void Show_OptionMenu();  // �ɼ� �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Category = "Event")
	void Launch_Lobby(int32 Player_Num, FName Server_Name, bool IsLan);  // �κ� �����ϰ� ȣ��Ʈ�� �����Ѵ�.
	//UFUNCTION(BlueprintCallable, Category = "Event")
	void Join_Server(IOnlineSessionPtr Sessions);  // ������ ����
	UFUNCTION(BlueprintCallable, Category = "Event")
	void Show_LodingScreen(); // �䱸�� �ε� ȭ�� ���
	//UFUNCTION(BlueprintCallable, Category = "Event")
	void Destroy_SessionCaller(class APlayerController PC); // ȣ�� �� ���� �ı�
	UFUNCTION(BlueprintCallable, Category = "Event")
	void Check_SaveGame();  // ���� ���� Ȯ�� �ϱ�

private:
	FName LobbyName = "LobbyMap";
	FString PlayerSettingsSave = "PlayerSettingsSave";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Check", meta = (AllowPrivateAccess = "true"))
	bool IsCreateSaveFile = false;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ServerSetting", meta = (AllowPrivateAccess = "true"))
	int32 MaxPlayer = 0;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ServerSetting", meta = (AllowPrivateAccess = "true"))
	FName ServerName;

	UFUNCTION(BlueprintPure)
	FString NetErrorToString(ENetworkFailure::Type FailureType);
	UFUNCTION(BlueprintPure)
	FString TravelErrorToString(ETravelFailure::Type FailureType);

};