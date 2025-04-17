#pragma once
#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual int get_size() const = 0;
    virtual void add_component(std::shared_ptr<FileSystemComponent> component) {}
    virtual void remove_component(std::shared_ptr<FileSystemComponent> component) {}
};

class File : public FileSystemComponent {
public:
    File(int size) : _size(size) {}
    int get_size() const override { return _size; }

private:
    int _size;
};

class Folder : public FileSystemComponent {
public:
    int get_size() const override {
        int total_size = 0;
        for (const auto& component : _components) {
            total_size += component->get_size();
        }
        return total_size;
    }

    void add_component(std::shared_ptr<FileSystemComponent> component) override {
        _components.push_back(component);
    }

    void remove_component(std::shared_ptr<FileSystemComponent> component) override {
        _components.erase(std::remove(_components.begin(), _components.end(), component), _components.end());
    }

private:
    std::vector<std::shared_ptr<FileSystemComponent>> _components;
};