#include "memento.hpp"
#include <iostream>

int main()
{
    Player player;
    player.setXp(42);
    player.setPseudo("Briochin");

    // Save the current state
    Player::Snapshot savedState = player.save();

    // Modify the object
    player.setXp(4242);
    player.setPseudo("MrPropre");

    // Output the modified object
    // Expected Output: "Current state: x = 100, y = World"
    std::cout << "Current state: pseudo = " << player.getPseudo() << ", xp = " << player.getXp() << std::endl;

    // Restore the object to its saved state
    player.load(savedState);
    
    // Output the restored object
	// Expected Output: "Restored state: x = 42, y = Hello"
    std::cout << "Restored state: pseudo = " << player.getPseudo() << ", xp = " << player.getXp() << std::endl;

    return 0;
}
