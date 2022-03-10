//
// Created by louis on 3/10/22.
//

#include <catch2/catch.hpp>

#include "src/client/MainController.h"
#include "src/client/MainModel.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <memory>

using json = nlohmann::json;

SCENARIO("Testing requests")
{
    MainController controller; // only call process request
    MainModel *model = controller.getMainModel();

    // You must test every requests that controller can process
    // To test a request, you must call the processRequest(std::string request) in MainController. The request string must be a valid json converted to string
    // To test if a request worked, you must call the appropriate getter in the model. For example, model->getLeaderboard() will return the leaderboard
    // You may use DatabaseHandler to fetch data but that is not mandatory
    // At the moment only a few tests will work (for example, the leaderboard should work)

}