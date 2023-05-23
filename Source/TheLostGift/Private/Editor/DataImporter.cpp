// Copyright © 2023 FireTaleStudio.

#include "Editor/DataImporter.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Item/BaseItemStructure.h"

void UDataImporter::ReadCSVFile()
{
	const FString URL = "https://docs.google.com/spreadsheets/d/1yc6pffdBGonPIqwydl65_LVC69GeDAhFsV9qB6AjRlI/export?format=csv&gid=353411397";

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

		for (const FString& CSVLine : CSVLines)
		{
			TArray<FString> CSVColumns = ParseCSVLineIntoColumns(CSVLine);
			FillStructFromColumns(CSVColumns);
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
		CSVLines.RemoveAt(0);

	return CSVLines;
}

// A function to parse a CSV line into columns
TArray<FString> UDataImporter::ParseCSVLineIntoColumns(const FString& CSVLine)
{
	TArray<FString> CSVColumns;
	CSVLine.ParseIntoArray(CSVColumns, TEXT(","), true);

	return CSVColumns;
}

// A function to fill a struct from columns
void UDataImporter::FillStructFromColumns(const TArray<FString>& CSVColumns)
{
	if (CSVColumns.Num() > 0)
	{
		FBaseItemStructure CSVStruct;

		// Get the structs UScriptStruct
		const UScriptStruct* Struct = FBaseItemStructure::StaticStruct();
		int32 ColumnIndex = 0;

		for (TFieldIterator<FProperty> PropertyIt(Struct); PropertyIt; ++PropertyIt)
		{
			const FProperty* Property = *PropertyIt;
            
			if (ColumnIndex < CSVColumns.Num())
			{
				FString ColumnValue = CSVColumns[ColumnIndex];
				Property->ImportText(*ColumnValue, Property->ContainerPtrToValuePtr<void>(&CSVStruct), PPF_None, nullptr);
				++ColumnIndex;
			}
		}

		UE_LOG(LogTemp, Error, TEXT("Item Name: %s"), *CSVStruct.Name);
		UE_LOG(LogTemp, Error, TEXT("Item Value: %i"), CSVStruct.Value);
		UE_LOG(LogTemp, Error, TEXT("--------------------------------"));
	}
}