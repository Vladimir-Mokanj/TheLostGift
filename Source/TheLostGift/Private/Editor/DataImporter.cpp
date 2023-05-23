// Copyright © 2023 FireTaleStudio.

#include "Editor/DataImporter.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Item/Weapon.h"

void UDataImporter::ReadCSVFile(const int32& DataSheetID)
{
	const FString URL = "https://docs.google.com/spreadsheets/d/1yc6pffdBGonPIqwydl65_LVC69GeDAhFsV9qB6AjRlI/export?format=csv&gid=" + FString::FromInt(DataSheetID);
	
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(URL);
	Request->SetVerb("GET");

	Request->OnProcessRequestComplete().Unbind();
	Request->OnProcessRequestComplete().BindUObject(this, &UDataImporter::OnDownloadComplete);

	Request->ProcessRequest();
}

void UDataImporter::OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, const bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid() && Response->GetContentType() == "text/csv")
	{
		const FString CSVData = Response->GetContentAsString();
		TArray<FString> CSVLines = ParseCSVDataIntoLines(CSVData);

		UItem* ItemAsset = NewObject<UWeapon>();
		
		for (const FString& CSVLine : CSVLines)
		{
			TArray<FString> CSVColumns = ParseCSVLineIntoColumns(CSVLine);
			CreateBlueprintAsset(CSVColumns, ItemAsset);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to download Google Sheet as CSV."));
	}
}

// A function to parse CSV data into lines
TArray<FString> UDataImporter::ParseCSVDataIntoLines(const FString& CSVData)
{
	TArray<FString> CSVLines;
	CSVData.ParseIntoArrayLines(CSVLines);

	// Remove header line
	if (CSVLines.Num() > 0)
	{
		CSVLines[0].ParseIntoArray(DataSheetValues, TEXT(","), true);
		CSVLines.RemoveAt(0);
	}

	return CSVLines;
}

// A function to parse a CSV line into columns
TArray<FString> UDataImporter::ParseCSVLineIntoColumns(const FString& CSVLine)
{
	TArray<FString> CSVColumns;
	CSVLine.ParseIntoArray(CSVColumns, TEXT(","), true);

	return CSVColumns;
}

// A function to create a blueprint asset from array of values
void UDataImporter::CreateBlueprintAsset(const TArray<FString>& CSVColumns, UItem* ItemAsset)
{
	int32 ColumnIndex = 0;

	for (const FString& DataSheetValue : DataSheetValues)
	{
		for (TFieldIterator<FProperty> PropIt(ItemAsset->GetClass()); PropIt; ++PropIt)
		{
			const FProperty* Property = *PropIt;
			FString PropertyName = Property->GetName();
	    
			if (PropertyName == DataSheetValue)
			{
				FString ColumnValue = CSVColumns[ColumnIndex];
				Property->ImportText(*ColumnValue, Property->ContainerPtrToValuePtr<void>(ItemAsset), PPF_None, nullptr);
				++ColumnIndex;
				break;
			}
		}
	}

	ItemAsset->Id = ItemAsset->GetHashCode();
	UE_LOG(LogTemp, Error, TEXT("Name: %s, id: %i"), *ItemAsset->Name, ItemAsset->Id);
}