#pragma once

class Feature {
public:
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void unload() = 0;
	virtual const std::string& get_name() const = 0;
};