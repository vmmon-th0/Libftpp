#include "memento.hpp"

Memento::Snapshot Memento::save()
{
    Snapshot snapshot;
    this->_saveToSnapshot(snapshot);
    return snapshot;
}

void Memento::load(const Snapshot &state)
{
    this->_loadFromSnapshot(state);
}

void Memento::Snapshot::setSnapshot(const std::string &key, std::any val)
{
    this->_snap[key] = val;
}

std::any Memento::Snapshot::getSnapshot(const std::string &key) const
{
    auto it = this->_snap.find(key);
    return (it != this->_snap.end()) ? it->second : std::any();
}

bool Memento::Snapshot::contains(const std::string &key) const
{
    return this->_snap.find(key) != this->_snap.end();
}

std::string Memento::Snapshot::getCreationDate() const
{
    return this->_date;
}

MainCharacter::MainCharacter() : _pseudo("default"), _xp(100)
{
}

void MainCharacter::setPseudo(const std::string &pseudo)
{
    this->_pseudo = pseudo;
}

void MainCharacter::setXp(uint8_t xp)
{
    this->_xp = xp;
}

std::string MainCharacter::getPseudo() const
{
    return this->_pseudo;
}

uint16_t MainCharacter::getXp() const
{
    return this->_xp;
}

void MainCharacter::_saveToSnapshot(Snapshot &snapshot)
{
    snapshot.setSnapshot(KEY_PSEUDO, this->_pseudo);
    snapshot.setSnapshot(KEY_XP, static_cast<uint16_t>(_xp));
}

void MainCharacter::_loadFromSnapshot(const Snapshot &snapshot)
{
    if (snapshot.contains(KEY_PSEUDO))
    {
        try
        {
            this->_pseudo = std::any_cast<std::string>(snapshot.getSnapshot(KEY_PSEUDO));
        }
        catch (const std::bad_any_cast &)
        {
            std::cerr << "Error: Invalid pseudo type in snapshot\n";
        }
    }

    if (snapshot.contains(KEY_XP))
    {
        try
        {
            this->_xp = std::any_cast<uint16_t>(snapshot.getSnapshot(KEY_XP));
        }
        catch (const std::bad_any_cast &)
        {
            std::cerr << "Error: Invalid XP type in snapshot\n";
        }
    }
}