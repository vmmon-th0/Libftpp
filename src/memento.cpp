#include "memento.hpp"

Memento::Snapshot Memento::save() const
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

Player::Player() : _pseudo("default"), _xp(100)
{
}

void Player::setPseudo(const std::string &pseudo)
{
    this->_pseudo = pseudo;
}

void Player::setXp(uint16_t xp)
{
    this->_xp = xp;
}

std::string Player::getPseudo() const
{
    return this->_pseudo;
}

uint16_t Player::getXp() const
{
    return this->_xp;
}

void Player::_saveToSnapshot(Memento::Snapshot &snapshot) const
{
    snapshot.setSnapshot(_KEY_PSEUDO, this->_pseudo);
    snapshot.setSnapshot(_KEY_XP, static_cast<uint16_t>(_xp));
}

void Player::_loadFromSnapshot(const Memento::Snapshot &snapshot)
{
    if (snapshot.contains(_KEY_PSEUDO))
    {
        try
        {
            this->_pseudo = std::any_cast<std::string>(snapshot.getSnapshot(_KEY_PSEUDO));
        }
        catch (const std::bad_any_cast &)
        {
            std::cerr << "Error: Invalid pseudo type in snapshot\n";
        }
    }

    if (snapshot.contains(_KEY_XP))
    {
        try
        {
            this->_xp = std::any_cast<uint16_t>(snapshot.getSnapshot(_KEY_XP));
        }
        catch (const std::bad_any_cast &)
        {
            std::cerr << "Error: Invalid XP type in snapshot\n";
        }
    }
}