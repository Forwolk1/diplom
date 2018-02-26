

#include <G4RunManager.hh>
#include <G4MTRunManager.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <QBBC.hh>
#include <Shielding.hh>
#include "GeantGeometry.h"

int main(int argc, char** argv)
{
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(nullptr));

    auto runManager = new G4RunManager;
    runManager->SetUserInitialization(new GeantGeometry());
    runManager->SetUserInitialization(new Shielding);


    runManager->Initialize();

#ifdef G4VIS_USE
    auto visManager = new G4VisExecutive;
    visManager->Initialize();
#endif

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc != 1) {
        std::string command = "/control/execute ";
        std::string fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else {
        // interactive mode : define UI session
#ifdef G4UI_USE
        G4UIExecutive *ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute init_vis.mac");
#else
        UImanager->ApplyCommand("/control/execute init.mac");
#endif
        ui->SessionStart();
        delete ui;
#endif
    }




    delete visManager;
    delete runManager;
}

