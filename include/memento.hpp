#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include <any>
#include <cstdint>
#include <map>
#include <iostream>
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

        Snapshot save();
        void load(const Memento::Snapshot &state);

        virtual void _saveToSnapshot(Memento::Snapshot &snapshot) = 0;
        virtual void _loadFromSnapshot(const Memento::Snapshot &snapshot) = 0;
};

class MainCharacter : public Memento
{
    public:
        MainCharacter();

        void setPseudo(const std::string &pseudo);
        void setXp(uint8_t xp);
        std::string getPseudo() const;
        uint16_t getXp() const;

    private:
        void _saveToSnapshot(Memento::Snapshot &snapshot) override;
        void _loadFromSnapshot(const Memento::Snapshot &snapshot) override;

        static inline const std::string KEY_XP = "xp";
        static inline const std::string KEY_PSEUDO = "pseudo";

        std::string _pseudo;
        uint16_t _xp;
};

#endif