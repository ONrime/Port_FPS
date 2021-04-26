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

	void Show_MainMenu();  // 메인 메뉴 화면 전환 and 마우스 활성화
	void Show_HostMenu();  // 호스트 메뉴 화면 전환 and 마우스 활성화
	void Show_ServerMenu();  // 서버 메뉴 화면 전환 and 마우스 활성화
	void Option_Menu();  // 옵션 메뉴 화면 전환 and 마우스 활성화
	void Launch_Lobby(int32 Player_Num, FText Server_Name, bool IsLan);  // 로비 메뉴 활성화
	void Show_LoddingScreen();  // 로비 메뉴 활성화

	

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ServerSetting", meta = (AllowPrivateAccess = "true"))
	int32 MaxPlayer = 0;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ServerSetting", meta = (AllowPrivateAccess = "true"))
	FText ServerName;

};