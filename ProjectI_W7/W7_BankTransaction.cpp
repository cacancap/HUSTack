#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Account {
    long long sent = 0;
    std::vector<int> recipients;
};

bool hasCycle(const std::vector<Account>& accounts, int start, int length) {
    if (length < 1 || static_cast<std::size_t>(length) > accounts.size()) return false;

    struct Frame {
        int account;
        std::size_t nextRecipient;
    };

    std::vector<bool> onPath(accounts.size(), false);
    std::vector<Frame> path;
    path.reserve(length);
    path.push_back({start, 0});
    onPath[start] = true;

    while (!path.empty()) {
        Frame& frame = path.back();
        const auto& recipients = accounts[frame.account].recipients;
        if (path.size() == static_cast<std::size_t>(length)) {
            if (std::binary_search(recipients.begin(), recipients.end(), start)) return true;
        } else if (frame.nextRecipient < recipients.size()) {
            int next = recipients[frame.nextRecipient++];
            if (!onPath[next]) {
                onPath[next] = true;
                path.push_back({next, 0});
            }
            continue;
        }

        onPath[frame.account] = false;
        path.pop_back();
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::map<std::string, int> accountIds;
    std::vector<Account> accounts;
    auto getAccountId = [&](const std::string& name) {
        auto [entry, inserted] = accountIds.try_emplace(name, static_cast<int>(accounts.size()));
        if (inserted) accounts.emplace_back();
        return entry->second;
    };

    long long transactionCount = 0;
    long long totalMoney = 0;
    std::string from, to, time, atm;
    int amount;
    while (std::cin >> from && from != "#") {
        std::cin >> to >> amount >> time >> atm;
        int sender = getAccountId(from);
        int recipient = getAccountId(to);
        ++transactionCount;
        totalMoney += amount;
        accounts[sender].sent += amount;
        accounts[sender].recipients.push_back(recipient);
    }

    // Parallel transactions count separately in totals but form one graph edge.
    for (Account& account : accounts) {
        auto& recipients = account.recipients;
        std::sort(recipients.begin(), recipients.end());
        recipients.erase(std::unique(recipients.begin(), recipients.end()), recipients.end());
    }

    std::string query, name;
    while (std::cin >> query && query != "#") {
        if (query == "?number_transactions") {
            std::cout << transactionCount << '\n';
        } else if (query == "?total_money_transaction") {
            std::cout << totalMoney << '\n';
        } else if (query == "?list_sorted_accounts") {
            for (auto it = accountIds.begin(); it != accountIds.end(); ++it) {
                if (it != accountIds.begin()) std::cout << ' ';
                std::cout << it->first;
            }
            std::cout << '\n';
        } else if (query == "?total_money_transaction_from") {
            std::cin >> name;
            auto account = accountIds.find(name);
            std::cout << (account == accountIds.end() ? 0 : accounts[account->second].sent) << '\n';
        } else if (query == "?inspect_cycle") {
            int length;
            std::cin >> name >> length;
            auto account = accountIds.find(name);
            std::cout << (account != accountIds.end() && hasCycle(accounts, account->second, length)) << '\n';
        }
    }
}
