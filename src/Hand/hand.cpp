#include "hand.h"
#include "../Game/game.h"

const float Hand::rotationAngle = 12.5f;

Hand::Hand(int aBet)
{
    bet = aBet;
    cards = std::vector<Card>();

    Reset();

    coefficients = std::map<int, float>({
        {WIN_REGULAR, 1.0f},
        {WIN_BLACKJACK, 1.5f},
        {PUSH, 0.0f},
        {LOSS, -1.0f}
    });
}

SplitHand::SplitHand(int aBet): Hand(aBet)
{
    isSplit = true;
}

void Hand::AddCard(Card c)
{
    cards.push_back(c);
    Update();
}

void Hand::Update()
{
    cards.back().TurnFaceUp();
    int rank = cards.back().GetRank();
    minScore += rank > 10 ? 10 : rank;

    hasAce = hasAce || rank == 1;
}

void Hand::SetActive(bool a)
{
    isActive = a;
}

void Hand::Double()
{
    bet *= 2;
    isDoubled = true;
}

Hand Hand::Split()
{
    isSplit = true;
    Hand output = SplitHand(bet);

    output.AddCard(cards.back());
    cards.pop_back();

    minScore /= 2;

    return output;
}

bool Hand::IsSplittable()
{
    if(cards.size() != 2){
        return false;
    }

    int firstRank = cards[0].GetRank();
    int secondRank = cards[1].GetRank();

    return (firstRank >= 10 && secondRank >= 10) || firstRank == secondRank;
}

bool Hand::IsSplitAce()
{
    return cards[0].GetRank() == 1 && isSplit;
}

bool Hand::IsBlackJack()
{
    return cards.size() == 2 && GetScore() == 21 && !isSplit;
}

bool Hand::IsBusted()
{
    return minScore > 21;
}

void Hand::Draw(Texture2D &spritesheet, Vector2 position)
{
    float startingAngle = -rotationAngle * (cards.size() - 1)/2.0f;

    for (size_t i = 0; i < cards.size(); i++)
    {
        cards[i].Draw(position, spritesheet, startingAngle + rotationAngle * i, isActive);
    }
    PrintScore(position);
}

void Hand::Discard(std::vector<Card> &discardPile)
{
    while(!cards.empty())
    {
        discardPile.push_back(cards.back());
        cards.pop_back();
    }
    Reset();
}

void Hand::Reset()
{
    minScore = 0;
    winnings = 0;
    hasAce = false;
    isActive = true;

    isSplit = false;
    isDoubled = false;
    isResolved = false;
}

void Hand::PrintScore(Vector2 position)
{
    if (minScore == 0)
    {
        return;
    }

    std::string stringTemplate = "";

    if (IsBusted())
    {
        stringTemplate = std::to_string(minScore) + ": Bust";
    }
    else if (IsBlackJack())
    {
        stringTemplate = "Blackjack!";
    }
    else
    {
        stringTemplate += std::to_string(minScore);
        stringTemplate += minScore != GetScore() ? " / " + std::to_string(GetScore()) : "";
    }

    const char* text = stringTemplate.c_str();

    Vector2 offset = {-MeasureText(text, Game::fontSize)/2.0f, DrawHandler::margin};
    Vector2 textPosition = Vector2Add(position, offset);

    Color col = isActive ? WHITE : DARKGRAY;

    DrawText(text, textPosition.x, textPosition.y, Game::fontSize, col);
    PrintBet({position.x, textPosition.y});
}

void Hand::PrintBet(Vector2 position)
{
    const float lineSpace = 2.0f;

    std::string stringTemplate = bet == 0 ? "Dealer" : "Bet: " + std::to_string(bet);

    if (isResolved)
    {
        if (winnings == 0)
        {
            stringTemplate += ", push";
        }
        else if (winnings < 0)
        {
            stringTemplate += ", loses";
        }
        else
        {
            stringTemplate += ", wins " + std::to_string(winnings);
        }
    }

    const char* text = stringTemplate.c_str();
    int textWidth = MeasureText(text, Game::fontSize);

    Vector2 offset = {-textWidth/2.0f, Game::fontSize + lineSpace};
    Vector2 textPosition = Vector2Add(position, offset);
    Color col = isActive ? WHITE : DARKGRAY;

    DrawText(text, textPosition.x, textPosition.y, Game::fontSize, col);
}

int Hand::GetBet()
{
    return bet;
}

int Hand::GetMinScore()
{
    return minScore;
}

int Hand::GetScore()
{
    int output = minScore;

    if (hasAce && minScore <= 11){
        output += 10;
    }

    return output;
}

int Hand::Resolve(Hand dealerHand)
{
    Outcome outcome = PUSH;
    isResolved = true;

    if(IsBlackJack() && !dealerHand.IsBlackJack())
    {
        outcome = WIN_BLACKJACK;
    }
    else if(dealerHand.IsBlackJack() && IsBlackJack())
    {
        outcome = PUSH;
    }
    else if(dealerHand.IsBlackJack() || IsBusted() || (!dealerHand.IsBusted() && GetScore() < dealerHand.GetScore()))
    {
        outcome = LOSS;
    }
    else if (GetScore() > dealerHand.GetScore() || (dealerHand.IsBusted() && !IsBusted()))
    {
        outcome = WIN_REGULAR;
    }
    else
    {
        outcome = PUSH;
    }

    winnings = (int)(bet * coefficients[outcome]);
    return winnings;
}
