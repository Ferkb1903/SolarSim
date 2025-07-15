//================================================================
// Archivo: src/SolarSim.cc (Modificado para nuevos nombres de archivo)
//================================================================
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include <string>

int main(int argc, char** argv)
{
    if (argc < 2) {
        G4cerr << "Error: Debes especificar la configuración." << G4endl;
        G4cerr << "Uso: " << argv[0] << " <con|sin> [archivo_macro]" << G4endl;
        return 1;
    }

    G4String config = argv[1];
    G4bool withUmbrella = false;
    if (config == "con") {
        withUmbrella = true;
    } else if (config != "sin") {
        G4cerr << "Error: El primer argumento debe ser 'con' o 'sin'." << G4endl;
        return 1;
    }
    
    // Nombres de archivo explícitos para los datos de la PIEL
    G4String outputFilename = withUmbrella ? "con_sombrilla_hits.csv" : "sin_sombrilla_hits.csv";

    auto* runManager = new G4RunManager();
    runManager->SetUserInitialization(new DetectorConstruction(withUmbrella, outputFilename));
    runManager->SetUserInitialization(new QGSP_BERT());
    runManager->SetUserInitialization(new ActionInitialization());
    
    G4UIExecutive* ui = nullptr;
    if (argc == 2) { 
        ui = new G4UIExecutive(argc, argv);
    }
    
    runManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (ui) { 
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
        delete visManager;
    }
    else { 
        G4String command = "/control/execute ";
        G4String fileName = argv[2];
        UImanager->ApplyCommand(command + fileName);
    }

    delete runManager;
    return 0;
}