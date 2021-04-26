// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
	virtual void Init() override;

	DECLARE_EVENT(UGameInfo_Instance, FGameMenu);
	DECLARE_EVENT_ThreeParams(UGameInfo_Instance, FGameLaunch, int32, FText, bool);

protected:

public:
	FGameMenu ShowMainMenu;
	FGameMenu ShowHostMenu;
	FGameMenu ShowServerMenu;
	FGameMenu ShowOptionMenu;
	FGameMenu ShowLoddingScreen;
	FGameLaunch LaunchLobby;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* MainMenu_WB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* HostMenu_WB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* ServerMenu_WB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu", meta = (AllowPrivateAccess = "true"))
		class UUserWidget* OptionMenu_WB;

	TSubclassOf<class UUserWidget> MainMenu_Class; 
	TSubclassOf<class UUserWidget> HostMenu_Class;
	TSubclassOf<class UUserWidget> ServerMenu_Class;
	TSubclassOf<class UUserWidget> OptionMenu_Class;

private:

	void Show_MainMenu();  // ���� �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	void Show_HostMenu();  // ȣ��Ʈ �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	void Show_ServerMenu();  // ���� �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	void Option_Menu();  // �ɼ� �޴� ȭ�� ��ȯ and ���콺 Ȱ��ȭ
	void Launch_Lobby(int32 Player_Num, FText Server_Name, bool IsLan);  // �κ� �޴� Ȱ��ȭ
	void Show_LoddingScreen();  // �κ� �޴� Ȱ��ȭ

	

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ServerSetting", meta = (AllowPrivateAccess = "true"))
	int32 MaxPlayer = 0;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ServerSetting", meta = (AllowPrivateAccess = "true"))
	FText ServerName;

};