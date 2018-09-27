import OnePyPlus as op
from op_analysis.analysis import Analysis


def dict_to_table(dict_data):
    for key, value in dict_data.items():
        if not isinstance(value, str):
            dict_data[key] = str(value)

    max_key_len = max([len(i) for i in dict_data])+1
    max_value_len = max([len(i) for i in dict_data.values()])+1
    total_len = max_key_len+max_value_len+3

    print(f'+{total_len*"-"}+')

    for key, value in dict_data.items():
        print(f'|{key.ljust(max_key_len)} | {value.rjust(max_value_len)}|')
    print(f'+{total_len*"-"}+')


class Output:
    def __init__(self, go: op.OnePiece):
        self.analysis = Analysis(go)

    def show(self):
        dict_to_table(self.analysis.general_summary())
        print(self.analysis.detail_summary())
