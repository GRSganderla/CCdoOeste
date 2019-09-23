import { createSwitchNavigator, createAppContainer } from 'react-navigation';

import Login from '../view/Login';
import Perdidos from '../view/Perdido';
import Menu from './menu';

const mainNavigation = createSwitchNavigator({
  Login,
  Menu,
});

export default createAppContainer(mainNavigation);