#include "MenuData.h"
#include "ActionData.h"
#include <vector>
#include <map>
#include <iostream>

// empty constructor
MenuData::MenuData( ) {

}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {    
    // appends name to the collection of names
    mNames.push_back(name);

    mMapAction[name] = func;
    mMapDesc[name] = description;

}

const std::vector<std::string>& MenuData::getNames() const {
    return mNames;
}


ActionFunctionType MenuData::getFunction(const std::string& name) {
    // If name is a key in the action function map, return the function associated with it. If name is not a key, return 0.

     if (mMapAction.find(name) != mMapAction.end()) {
        return mMapAction[name];
    } else {
        return 0;
    }
}

const std::string& MenuData::getDescription(const std::string& name) {

    static std::string empty = "";
    
    if (mMapDesc.find(name) != mMapDesc.end()) {
        return mMapDesc[name];
    } else {
        return empty;
    }
}



