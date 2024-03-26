#ifndef _MENUDATA_H_
#define _MENUDATA_H_

#include "ActionData.h"
#include <vector>
#include <map>
#include <iostream>

typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData {


public:

    MenuData();
    void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
    const std::vector<std::string>& getNames() const;
    ActionFunctionType getFunction(const std::string& name);
    const std::string& getDescription(const std::string& name);


protected:

    std::vector<std::string> mNames;
    std::map<std::string,ActionFunctionType> mMapAction;
    std::map<std::string,std::string> mMapDesc;

};


#endif /* _MENUDATA_H_ */