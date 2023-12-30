#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Feature.h"

class Featurectl {
private:
    std::vector<std::unique_ptr<Feature>> features;

public:
    void load_feature(std::unique_ptr<Feature> feature) {
        feature->load();
        features.push_back(std::move(feature));
    }

    Feature* get_feature(const std::string& name) const {
        for (const auto& feature : features)
        {
            if (feature->get_name() == name)
                return feature.get();
        }
        return nullptr;
    }

};

inline Featurectl featurectl;