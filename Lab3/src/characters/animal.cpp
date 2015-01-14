#include <characters/animal.h>

using namespace lab3::characters;


Animal::Animal(const std::string &name, const std::string &type, Place *place, Place *natural_habitat, int reproduction_frequency)
    : Character(name,type, place), natural_habitat_(natural_habitat),
      p_food_(0.8), p_go_(0.2),
      reproduction_frequency_(reproduction_frequency),
      days_since_last_reproduced_(0)
{
    this->talk_msgs_ =
    {
        "Grrrr"
    };
}

Animal::~Animal()
{}

ActionResult Animal::action(bool display_info)
{
    // ** Decide whether to fight, look for food or go elsewhere
    Character* enemy = this->lookForEnemies();
    double p_fight = (enemy != nullptr && !enemy->isFighting()) ? this->p_fight_ : 0;

    std::vector<double> probabilities = {p_fight, this->p_food_, this->p_go_};
    std::vector<std::string> commands = {CMD_FIGHT, CMD_LOOK_FOOD, CMD_GO};
    lab3::utils::normalizeProbabilities(probabilities);

    // Select command at random
    std::string cmd = lab3::utils::getRandomCommandProbs(commands, probabilities);
    if(cmd == CMD_FIGHT)
    {
        return this->fight(*enemy);
    }
    else if (cmd == CMD_LOOK_FOOD)
    {
        return this->lookForFood();

    }
    else if (cmd == CMD_GO)
    {
        // Get directions
        const std::map<std::string, Place*> directions = this->currentPlace()->directions();
        // Get random direction
        int d = lab3::utils::iRand(0, directions.size()-1);
        int i = 0;
        for(auto it = directions.begin();  it != directions.end(); ++it, ++i)
        {
            if (i == d)
            {
                return this->go(it->first);
            }
        }
    }
    return EVENT_NULL;
}

bool Animal::lookForFood()
{
    std::stringstream ss;
    ss << this->name() <<" is looking for food...";
    lab3::utils_io::print_newline(ss.str());

    double p_food = *this->currentPlace() == *this->natural_habitat_ ? PROB_FOOD_IN : PROB_FOOD_OUT;

    if(lab3::utils::eventHappens(p_food))
    {
        lab3::utils_io::print_newline("It found food!");
        this->add_life(LIFE_FOOD);
        return true;
    }
    lab3::utils_io::print_newline("It did not find food");
    return false;
}
