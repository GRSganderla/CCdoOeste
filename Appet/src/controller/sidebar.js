import React from 'react';
import { ScrollView, SafeAreaView, Text} from 'react-native';
import {createAppContainer} from 'react-navigation';
import {createDrawerNavigator} from 'react-navigation-drawer';
import {createStackNavigator} from 'react-navigation-stack';
import MinhaConta from '../view/MinhaConta';
import Adocao from '../view/Adocao';
import BottomTabs from './menubottom';

const HamburgerNavigation = createDrawerNavigator(
    {
        Tabs: BottomTabs,
    },
    {
    initialRouteName: 'Tabs',
    contentComponent: props => {
        return (
            <ScrollView>
                <SafeAreaView
                forceInset={{ top: 'always', horizontal: 'never' }}
            >
                <Text
                    onPress={() => {
                    props.navigation.navigate('MinhaConta');
                    props.navigation.closeDrawer();
                    }}
                >
                    Minha Conta
                </Text>
                <Text
                    onPress={() => {
                    props.navigation.navigate('Adocao');
                    props.navigation.closeDrawer();
                    }}
                    >
                    Adocao
                </Text>
                    </SafeAreaView>
                </ScrollView>
            )
        }
    }
 );
 const Stack = createStackNavigator(
    {
        Drawer: {
            screen: HamburgerNavigation,
            navigationOptions: {
                header: null,
            },
        },
        Parceria: Adocao,
        MinhaContaa: {
            screen: MinhaConta,
        }
    }
 );

export default createAppContainer(Stack);