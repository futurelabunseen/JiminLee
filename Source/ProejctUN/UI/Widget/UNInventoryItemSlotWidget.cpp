// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/UNInventoryItemSlotWidget.h"
#include "Item/ItemBase.h"
#include "UI/Widget/UNInventoryTooltip.h"
#include "UI/Widget/UNDragItemVisual.h"
#include "UI/UNItemDragDropOperation.h"
#include "Character/UNPlayerCharacter.h"
#include "UI/UNInventoryComponent.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUNInventoryItemSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CreateToolTip();
}

void UUNInventoryItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSlot();
}

FReply UUNInventoryItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		CheckItemTypeAndTryEquip();
		return Reply.Handled();
	}

	return Reply.Unhandled();
}

void UUNInventoryItemSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
}

void UUNInventoryItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (DragItemVisualClass)
	{
		const TObjectPtr<UUNDragItemVisual> DragVisual = CreateWidget<UUNDragItemVisual>(this, DragItemVisualClass);
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());

		ItemReference->NumericData.bIsStackable ? DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity)) : DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

		UUNItemDragDropOperation* DragItemOperation = NewObject<UUNItemDragDropOperation>();
		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;

		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;
	}
}

bool UUNInventoryItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}




void UUNInventoryItemSlotWidget::CreateToolTip()
{
	if (ToolTipClass)
	{
		UUNInventoryTooltip* ToolTip = CreateWidget<UUNInventoryTooltip>(this, ToolTipClass);
		ToolTip->InventorySlotBeingHovered = this;
		SetToolTip(ToolTip);
	}
}

void UUNInventoryItemSlotWidget::UpdateSlot()
{
	if (ItemReference)
	{
		switch (ItemReference->ItemQuality)
		{
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(FLinearColor::White);
			break;
		case EItemQuality::Quality:
			ItemBorder->SetBrushColor(FLinearColor::Green);
			break;
		case EItemQuality::Masterwork:
			ItemBorder->SetBrushColor(FLinearColor::Blue);
			break;
		case EItemQuality::Grandmaster:
			ItemBorder->SetBrushColor(FLinearColor::Yellow);
			break;
		default:;
		}

		ItemIcon->SetBrushFromTexture(ItemReference->AssetData.Icon);

		if (ItemReference->NumericData.bIsStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UUNInventoryItemSlotWidget::CheckItemTypeAndTryEquip()
{
	UE_LOG(LogTemp, Log, TEXT("CHeck"));
	if (AUNPlayerCharacter* PlayerCharacter = Cast<AUNPlayerCharacter>(GetOwningPlayerPawn()))
	{
		if (UUNInventoryComponent* Inventory = PlayerCharacter->GetInventoryComponent())
		{
			switch (ItemReference->ItemType)
			{
			case EItemType::Weapon:
				UE_LOG(LogTemp, Log, TEXT("Weapon"));
				Inventory->WeaponSlot = ItemReference;
				Inventory->RemoveAmountOfItem(ItemReference, 1);
				break;
			case EItemType::Armor:
				Inventory->ArmorSlot = ItemReference;
				Inventory->RemoveAmountOfItem(ItemReference, 1);
				break;
			default:
				break;
			}
		}
	}
}
