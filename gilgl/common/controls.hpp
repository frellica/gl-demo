//
//  controls.hpp
//  gilgl
//
//  Created by frellica on 16/2/2.
//  Copyright © 2016年 frellica. All rights reserved.
//

#ifndef controls_hpp
#define controls_hpp

void computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif /* controls_hpp */
