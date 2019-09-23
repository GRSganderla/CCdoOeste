import React from 'react';
import { Icon } from 'react-native';
import Perdidos from '../view/Perdido';
import Adocao from '../view/Adocao';
import Vaquinha from '../view/Vaquinha';
import Discussao from '../view/Discussao';
import { createBottomTabNavigator } from 'react-navigation-tabs';  
import { createAppContainer } from 'react-navigation';
import { tabBarIcon} from 'react-navigation';

const Tabs = createBottomTabNavigator({
    Perdidos: Perdidos,
    Adocao: Adocao,
    Vaquinha: Vaquinha,
    Discussões: Discussao
}, 
{
    defaultNavigationOptions: ({})
});

export default createAppContainer(Tabs);