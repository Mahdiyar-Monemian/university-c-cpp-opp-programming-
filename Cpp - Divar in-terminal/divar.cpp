#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <functional>

using namespace std;

class Advertise
{
public:
    Advertise(string title, string username) : ad_title(title), ad_user(username) {}
    Advertise(string title, string username, string tag_name) : ad_title(title), ad_user(username), tag(tag_name) {}

    string get_title()
    {
        return ad_title;
    }

    string get_username()
    {
        return ad_user;
    }

    string get_tag()
    {
        return tag;
    }

    int compare_with_ad(Advertise *ad_2)
    {
        if (ad_2->get_title() == this->get_title() && ad_2->get_username() == this->get_username())
        {
            return 2;
        }
        else if (ad_2->get_title() == this->get_title())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

private:
    string ad_title;
    string ad_user;
    string tag;
};

class User
{
public:
    User(string name) : username(name) {}
    vector<Advertise*> self_ads;
    vector<Advertise*> favorites;
    string get_username()
    {
        return username;
    }

    bool favorites_contain(Advertise *fav_ad)
    {
        for (const auto &ad : favorites)
        {
            string ad_title = ad->get_title();
            string fav_title = fav_ad->get_title();
            if (ad_title == fav_title)
            {
                return true;
            }
        }
        return false;
    }

    void add_favorite(Advertise *ad)
    {
        if (favorites_contain(ad))
        {
            cout << "already favorite" << endl;
        }
        else
        {
            favorites.push_back(ad);
        }
    }

    void delete_favorite(int fav_index)
    {
        favorites.erase(favorites.begin() + fav_index);
    }

    int find_fav_index(string title)
    {
        for (int i = 0; i < favorites.size(); i++)
        {
            if (favorites[i]->get_title() == title)
            {
                return i;
            }
        }
        cout << "already not favorite" << endl;
        return -1;
    }

    void display_favs()
    {
        for (size_t i = 0; i < favorites.size(); i++)
        {
            cout << favorites[i]->get_title();
            if (i < favorites.size() - 1)
            {
                cout << " ";
            }
        }
        cout << "\n";
    }

    void display_favs(string tag)
    {
        for (size_t i = 0; i < favorites.size(); i++)
        {
            if (favorites[i]->get_tag() == tag)
            {
                cout << favorites[i]->get_title();
                if (i < favorites.size() - 1)
                {
                    cout << " ";
                }
            }
        }
        cout << "\n";
    }

    bool compare_with_user(User *user_2)
    {
        return user_2->get_username() == this->get_username();
    }

    void delete_self_ads(string title) {
        int index = find_ads_index(title);
        self_ads.erase(self_ads.begin() + index);
        return;
    }

    int find_ads_index (string title) {
        int index;
        for (int i = 0; i < self_ads.size(); i++) {
            if (self_ads[i]->get_title() == title) {
                return i;
            }
        }
    }
private:
    string username;
};

class Divar
{
public:
    Divar() {}
    bool user_contain(string target_username)
    {
        for (const auto &user : this->users)
        {
            if (user->get_username() == target_username)
            {
                return true;
            }
        }
        return false;
    }
    bool ad_contain(string target_title)
    {
        for (const auto &ad : this->ads)
        {
            if (ad->get_title() == target_title)
            {
                return true;
            }
        }
        return false;
    }

    int find_ad_index(string title, string username)
    {
        Advertise tmp(title, username);

        for (int i = 0; i < this->ads.size(); i++)
        {
            Advertise *current = this->ads[i];
            int comparison_result = tmp.compare_with_ad(current);
            if (comparison_result != 0)
            {
                return i;
            }
        }
        cout << "invalid title" << endl;
        return -1;
    }
    int find_ad_index_user(string title, string username)
    {
        Advertise tmp(title, username);
        bool access_denied = false;

        for (int i = 0; i < this->ads.size(); i++)
        {
            Advertise *current = this->ads[i];
            int comparison_result = tmp.compare_with_ad(current);
            if (comparison_result == 2)
            {
                return i;
            }
            else if (comparison_result == 1)
            {
                access_denied = true;
            }
        }

        if (access_denied)
        {
            cout << "access denied" << endl;
            return -1;
        }
        cout << "invalid title" << endl;
        return -1;
    }
    int find_user_index(string username)
    {
        if (!user_contain(username))
        {
            cout << "invalid username" << endl;
            return -1;
        }

        User tmp(username);
        for (int i = 0; i < this->users.size(); i++)
        {
            User *current = this->users[i];
            int comparison_result = tmp.compare_with_user(current);
            if (comparison_result)
            {
                return i;
                break;
            }
        }
        return -1;
    }

    void add_user(string username)
    {
        if (user_contain(username) == false)
        {
            User *newUser = new User(username);
            this->users.push_back(newUser);
            cout << "registered successfully" << endl;
        }
        else
        {
            cout << "invalid username" << endl;
        }
    }
    void add_ad(string username, string title)
    {
        if (user_contain(username) == false)
        {
            cout << "invalid username" << endl;
            return;
        }
        else if (ad_contain(title) == true)
        {
            cout << "invalid title" << endl;
            return;
        }
        else
        {
            Advertise *newAd = new Advertise(title, username);
            this->ads.push_back(newAd);
            int user_index = find_user_index(username);
            if (user_index != -1)
            {
                users[user_index]->self_ads.push_back(newAd);
            }
            cout << "posted successfully" << endl;
            return;
        }
    }
    void add_ad(string username, string title, string tag_name)
    {
        if (user_contain(username) == false)
        {
            cout << "invalid username" << endl;
            return;
        }
        else if (ad_contain(title) == true)
        {
            cout << "invalid title" << endl;
            return;
        }
        else
        {
            Advertise *newAd = new Advertise(title, username, tag_name);
            this->ads.push_back(newAd);
            int user_index = find_user_index(username);
            if (user_index != -1)
            {
                users[user_index]->self_ads.push_back(newAd);
            }
            cout << "posted successfully" << endl;
            return;
        }
    }
    void delete_ad(string username, string title)
    {
        if (!user_contain(username))
        {
            cout << "invalid username" << endl;
            return;
        }
        else
        {
            int found_ad = find_ad_index_user(title, username);
            int found_user = find_user_index(username);
            if (found_ad != -1)
            {
                ads.erase(ads.begin() + found_ad);
                users[found_user]->delete_self_ads(title);
                cout << "removed successfully" << endl;
                return;
            }
        }
    }
    void display_ads(string username)
    {
        int user_index = find_user_index(username);
        if (user_index == -1)
        {
            return;
        }
        else
        {   
            if (users[user_index]->self_ads.size() == 0) {
                cout << "\n";
                return;
            }
            for (size_t i = 0; i < users[user_index]->self_ads.size(); i++)
            {
                cout << users[user_index]->self_ads[i]->get_title();
                if (i < users[user_index]->self_ads.size() - 1)
                {
                    cout << " ";
                }
            }
            if (users[user_index]->self_ads.size() > 0) {
                cout << "\n";
            }
        }
    }
    void display_ads(string username, string tag_name)
    {
        int user_index = find_user_index(username);
        if (user_index == -1)
        {
            return;
        }
        else
        {
            for (size_t i = 0; i < users[user_index]->self_ads.size(); i++)
            {
                if (users[user_index]->self_ads[i]->get_tag() == tag_name)
                {
                    cout << users[user_index]->self_ads[i]->get_title();
                    if (i < users[user_index]->self_ads.size() - 1)
                    {
                        cout << " ";
                    }
                }
            }
            if (users[user_index]->self_ads.size() > 0) {
                cout << "\n";
            }
        }
    }

    void add_favorite(string username, string title)
    {
        int user_index = find_user_index(username);
        if (user_index == -1) {
            return;
        }
        int ad_index = find_ad_index(title, username);
        if (ad_index == -1) {
            return;
        }
        else if (users[user_index]->favorites_contain(ads[ad_index])) {
            cout << "already favorite" << endl;
            return;
        }
        else {
            users[user_index]->add_favorite(ads[ad_index]);
            cout << "added successfully" << endl;
        }
    }
    void delete_favorite(string username, string title)
    {
        int user_index = find_user_index(username);
        int ad_index = find_ad_index(title, username);
        int fav_index = users[user_index]->find_fav_index(title);
        if (user_index == -1 || ad_index == -1 || fav_index == -1)
        {
            return;
        }
        else
        {
            users[user_index]->delete_favorite(fav_index);
            cout << "removed successfully" << endl;
            return;
        }
    }
    void display_favorites(string username)
    {
        int user_index = find_user_index(username);
        if (user_index == -1)
        {
            return;
        }
        else
        {
            users[user_index]->display_favs();
        }
    }
    void display_favorites(string username, string tag)
    {
        int user_index = find_user_index(username);
        if (user_index == -1)
        {
            return;
        }
        else
        {
            users[user_index]->display_favs(tag);
        }
    }

    void process_query(string input){
        stringstream ss(input);
        string word;
        vector <string> words;

        while (ss >> word) {
            words.push_back(word);
        }
        int words_size = words.size();

        if (words[0] == "register") {
            this->add_user(words[1]);
        }
        else if (words[0] == "add_advertise") {
            if (words_size == 3) {
                this->add_ad(words[1], words[2]);
            }
            else if (words_size == 4) {
                this->add_ad(words[1], words[2], words[3]);
            }
        }
        else if (words[0] == "rem_advertise") {
            this->delete_ad(words[1], words[2]);
        }
        else if (words[0] == "list_my_advertises") {
            if (words_size == 2) {
                this->display_ads(words[1]);
            }
            else if (words_size == 3) {
                this->display_ads(words[1], words[2]);
            }
        }
        else if (words[0] == "add_favorite") {
            this->add_favorite(words[1], words[2]);
        }
        else if (words[0] == "rem_favorite") {
            this->delete_favorite(words[1], words[2]);
        }
        else if (words[0] == "list_favorite_advertises") {
            if (words_size == 2) {
                this->display_favorites(words[1]);
            }
            else if (words_size == 3) {
                this->display_favorites(words[1], words[2]);
            }
        }
    }
    void process_input()
    {
        int q;
        cin >> q;
        cin.ignore();
        for (int i = 0; i < q; i++)
        {
            string query_line;
            getline(cin, query_line);
            process_query(query_line);
        }
    }

private:
    vector<User *> users;
    vector<Advertise *> ads;
};

int main()
{
    Divar *divar = new Divar();
    divar->process_input();
}