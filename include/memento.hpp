#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include <any>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

class Memento
{
    public:
        virtual ~Memento() = default;

        class Snapshot
        {
            public:
                void setSnapshot(const std::string &key, std::any val);
                std::any getSnapshot(const std::string &key) const;
                bool contains(const std::string &key) const;
                std::string getCreationDate() const;

            private:
                std::map<std::string, std::any> _snap;
                std::string _date;
        };

        Snapshot save() const;
        void load(const Memento::Snapshot &state);

        virtual void _saveToSnapshot(Memento::Snapshot &snapshot) const = 0;
        virtual void _loadFromSnapshot(const Memento::Snapshot &snapshot) = 0;
};

class Player : public Memento
{
    public:
        Player();

        void setPseudo(const std::string &pseudo);
        void setXp(uint16_t xp);
        std::string getPseudo() const;
        uint16_t getXp() const;

    private:
        void _saveToSnapshot(Memento::Snapshot &snapshot) const override;
        void _loadFromSnapshot(const Memento::Snapshot &snapshot) override;

        // Todo -> static inline understanding
        const std::string _KEY_XP = "xp";
        const std::string _KEY_PSEUDO = "pseudo";

        std::string _pseudo;
        uint16_t _xp;
};

#endif