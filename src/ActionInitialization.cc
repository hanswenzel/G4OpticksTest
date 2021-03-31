#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "StackingAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"
#include "Ctx.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {
}

ActionInitialization::~ActionInitialization() {
}

void ActionInitialization::BuildForMaster() const {
    SetUserAction(new RunAction);
}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new StackingAction);

    Ctx* ctx = new Ctx();
    EventAction* eventAction = new EventAction(ctx);
    TrackingAction* ta = new TrackingAction(ctx);
    SteppingAction* sa = new SteppingAction(ctx);
    SetUserAction(eventAction);
    SetUserAction(ta);
    SetUserAction(sa);
}