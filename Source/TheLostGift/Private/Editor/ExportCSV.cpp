// Copyright © 2023 FireTaleStudio.


#include "Editor/ExportCSV.h"

#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"


void UExportCSV::ReadCSVFile()
{
	FString URL = "https://docs.google.com/spreadsheets/d/14TTwigcrjFwfRgIVtJLvxLCRWvuEk9ZgRkwrnJsP0nQ/export?format=csv";
    
        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
        Request->SetURL(URL);
        Request->SetVerb("GET");
    
        Request->OnProcessRequestComplete().BindUObject(this, &UExportCSV::OnDownloadComplete);
    
        Request->ProcessRequest();
}

void UExportCSV::OnDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid() && Response->GetContentType() == "text/csv")
	{
		FString CSVData = Response->GetContentAsString();

		FString SavePath = FPaths::ProjectDir() + "Saved/CSV/"; // Change this path as per your requirement
		FString FileName = "spreadsheet.csv";
		FString AbsoluteFilePath = SavePath + FileName;

		// Save the CSV data to a file
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (PlatformFile.CreateDirectoryTree(*SavePath))
		{
			FFileHelper::SaveStringToFile(CSVData, *AbsoluteFilePath);

			// CSV file has been successfully downloaded and saved
			UE_LOG(LogTemp, Warning, TEXT("Google Sheet downloaded and saved as CSV."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create directory for saving CSV file."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to download Google Sheet as CSV."));
	}
}
