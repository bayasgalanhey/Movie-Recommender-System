#ifndef IENTITY_H
#define IENTITY_H

#include <string>

class IEntity {
public:
    /**
     * @brief Get the ID of the movie
     * 
     * @return int 
     */
    virtual int getID() const = 0;
    /**
     * @brief Get the Name of the movie
     * 
     * @return std::string 
     */
    virtual std::string getName() const = 0;
    /**
     * @brief Display's the movies information
     * 
     */
    virtual void displayInfo() const = 0;
    /**
     * @brief Destroy the IEntity object
     * 
     */
    virtual ~IEntity() {}  
};




#endif //IEntity.h