import telebot
from telebot import types
import numpy as np
import pandas as pd


bot = telebot.TeleBot('5629208391:AAFowkQDqWnRxQ2u1IY4Qk45tExAhyGYukA')

read_file_excel = pd.read_excel('Students.xlsx')
read_file_excel.to_csv('Students.csv', index=False, header=True)
read_file_csv = pd.read_csv('Students.csv')
rfc = read_file_csv
rfc['id'] = np.NaN
rfc.to_csv('Students.csv')

read_file_timeTable_excel = pd.read_excel('Timetable.xlsx')
read_file_timeTable_excel.to_csv('Timetable.csv', index=False, header=True)
read_file_timeTable_csv = pd.read_csv('Timetable.csv')
rfc_tt = read_file_timeTable_csv


a = ''
b = ''
buttons = ['Оповестить']
less_amm = 3


@bot.message_handler(commands=['start'])
def start(message):
    msg_id = message.from_user.id
    if rfc[rfc['id'] == str(msg_id)].shape[0] == 0:
        markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
        btn1 = types.KeyboardButton('Регистрация')
        markup.add(btn1)
        bot.send_message(message.from_user.id, 'Привет! Для регистрации нажми на кнопку', reply_markup=markup)


@bot.message_handler(content_types=['text'])
def get_name(message):
    msg_t = message.text
    msg_id = message.from_user.id

    if msg_t == 'Регистрация':
        if rfc[rfc['id'] == str(msg_id)].shape[0] == 1:
            bot.send_message(msg_id, 'Вы уже зарегистрированы!')
            return

        markup = types.ReplyKeyboardRemove()
        bot.send_message(msg_id, 'Напиши свои фамилию и имя\nПример: Иванов Иван', reply_markup=markup)
        bot.register_next_step_handler(message, get_class)

    if msg_t == 'Оповестить':
        if rfc[rfc['id'] == str(msg_id)].shape[0] == 0:
            bot.send_message(msg_id, 'Нет доступа: вы не зарегистрированы!')
            return

        markup = types.ReplyKeyboardRemove()
        bot.send_message(msg_id, 'В какой день вы заболели?', reply_markup=markup)
        message_get_infection_day(message)
        # bot.register_next_step_handler(message, message_get_infection_day)


def get_class(message):
    global a
    a = message.text
    bot.send_message(message.from_user.id, 'Отлично! Теперь напиши класс, в котором учишься\nПример: 11И1')
    bot.register_next_step_handler(message, reg_finish)


def reg_finish(message):
    global b
    b = message.text
    if rfc[rfc['Name'] == a][rfc['Class'] == b].shape[0] == 1:
        rfc.loc[rfc[rfc['Name'] == a][rfc['Class'] == b]['num'], 'id'] = str(message.from_user.id)
        rfc.to_csv('Students.csv')

        global buttons
        markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
        for i in buttons:
            btni = types.KeyboardButton(i)
            markup.add(btni)
        bot.send_message(message.from_user.id, 'Великолепно! Регистрация прошла успешно!', reply_markup=markup)

    else:
        markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
        markup.add('Регистрация')
        bot.send_message(message.from_user.id, 'Такой ученик не учится в школе. Проверь введённые данные!',
                         reply_markup=markup)


def message_get_infection_day(message):
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    markup.add(buttons[0])
    get_inf_day_msg_list = ['Отмена оповещения', 'Понедельник', 'Вторник', 'Среда', 'Четверг', 'Пятница', 'Суббота']
    for i in get_inf_day_msg_list:
        btn_day_i = types.KeyboardButton(i)
        markup.add(btn_day_i)
    bot.send_message(message.from_user.id, 'Пожалуйста, нажмите на одну из соответствующих кнопок:', reply_markup=markup)
    bot.register_next_step_handler(message, get_infection_day)


def get_infection_day(message):
    msg_t = message.text
    msg_id = message.from_user.id

    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    for i in buttons:
        btni = types.KeyboardButton(i)
        markup.add(btni)

    if msg_t == 'Отмена оповещения':
        bot.send_message(msg_id, 'Отмена оповещения.', reply_markup=markup)
        return

    days_6 = ['Понедельник', 'Вторник', 'Среда', 'Четверг', 'Пятница', 'Суббота']
    try:
        msg_d = days_6.index(msg_t)
    except ValueError:
        message_get_infection_day(message)
        return

    msg_n = str(rfc[rfc['id'] == str(msg_id)]['Name'])  # msg_n - имя пользователя
    msg_n = msg_n[5: msg_n.find('\n')]
    msg_cl = str(rfc[rfc['id'] == str(msg_id)]['Class'])  # msg_cl - класс пользователя
    msg_cl = msg_cl[5: msg_cl.find('\n')]

    global less_amm
    mass_msgr = []
    for i in range(msg_d * less_amm,  (msg_d+1) * less_amm):
        msg_r = rfc_tt.loc[i, msg_cl]
        mass_msgr.append(msg_r)

    mass_inf_cl = []
    for j in rfc_tt.columns[1:]:
        for i in range(less_amm):
            ii = i + msg_d*less_amm

            if not(rfc_tt.loc[ii, j] in mass_msgr):
                continue

            if mass_msgr.index(rfc_tt.loc[ii, j]) > i:
                continue

            mass_inf_cl.append(j)
            break

    infection_notification = f'Внимание! Один из учеников заболел, и Вы тоже можете быть заражены!'
    for i in rfc[rfc['id'].isna() == False].index:
        if rfc.loc[i, 'Class'] in mass_inf_cl:
            crr_usr_id = rfc.loc[i, 'id']
            bot.send_message(crr_usr_id, infection_notification)
    bot.send_message(msg_id, 'Все ученики оповещены о вашей болезни.', reply_markup=markup)


print('Почти запущено!')

bot.polling(none_stop=True, interval=0)


